from _irmin_ffi import ffi, lib  # type: ignore
from typing import Optional, Sequence, Any, List, Union
import json


class Type:
    def __init__(self, ptr):
        self.type = ptr

    @staticmethod
    def unit() -> 'Type':
        return Type(lib.irmin_type_unit())

    @staticmethod
    def string() -> 'Type':
        return Type(lib.irmin_type_string())

    @staticmethod
    def json() -> 'Type':
        return Type(lib.irmin_type_json())

    @staticmethod
    def json_value() -> 'Type':
        return Type(lib.irmin_type_json_value())

    def __del__(self):
        lib.irmin_type_free(self.type)


class Value:
    def __init__(self, ptr, ty: Type):
        self.type = ty
        self.value = ptr

    @staticmethod
    def unit() -> 'Value':
        return Value(lib.irmin_value_unit(), Type.unit())

    @staticmethod
    def string(s: str) -> 'Value':
        return Value(lib.irmin_value_string(str.encode(s)), Type.string())

    @staticmethod
    def json(d: dict) -> 'Value':
        t = Type.json()
        s = str.encode(json.dumps(d))
        return Value(lib.irmin_value_of_string(t.type, s, len(s)), t)

    @staticmethod
    def json_value(d: Any) -> 'Value':
        t = Type.json_value()
        s = str.encode(json.dumps(d))
        return Value(lib.irmin_value_of_string(t.type, s, len(s)), t)

    def to_string(self) -> str:
        s = lib.irmin_value_get_string(self.value, ffi.NULL)
        st = ffi.string(s)
        lib.free(s)
        return bytes.decode(st)

    def __bytes__(self):
        s = lib.irmin_value_to_string(self.type.type, self.value, ffi.NULL)
        st = ffi.string(s)
        lib.free(s)
        return st

    def __str__(self):
        return bytes.decode(self.__bytes__())

    def __del__(self):
        lib.irmin_value_free(self.value)


class Contents:
    def __init__(self, f, ty, py_ty):
        self.python_type = py_ty
        self.f = f
        self.type = ty


class Schema:
    content_types = {
        "string": Contents(Value.string, Type.string(), str),
        "json": Contents(Value.json, Type.json(), dict),
        "json-value": Contents(Value.json_value, Type.json_value(), Any)
    }

    def __init__(self, ptr, c: str):
        self.schema = ptr
        self.contents = self.content_types[c]

    @staticmethod
    def git(contents="string"):
        return Schema(lib.irmin_schema_git(str.encode(contents)), contents)

    @staticmethod
    def pack(contents="string", hash: Optional[str] = None):
        h = ffi.NULL if hash is None else str.encode(hash)
        return Schema(lib.irmin_schema_pack(h, str.encode(contents)), contents)

    @staticmethod
    def mem(contents="string", hash: Optional[str] = None):
        h = ffi.NULL if hash is None else str.encode(hash)
        return Schema(lib.irmin_schema_mem(h, str.encode(contents)), contents)

    @staticmethod
    def fs(contents="string", hash: Optional[str] = None):
        h = ffi.NULL if hash is None else str.encode(hash)
        return Schema(lib.irmin_schema_fs(h, str.encode(contents)), contents)

    def __del__(self):
        lib.irmin_schema_free(self.schema)


class Config:
    def __init__(self, backend: Union[str, Schema], *args, **kwargs):
        if type(backend) == str:
            f = getattr(Schema, backend)
            self.schema = f(*args, **kwargs)
        else:
            self.schema = backend
        self.config = lib.irmin_config_new(self.schema.schema)

    def root(self, root: str):
        value = Value.string(root)
        lib.irmin_config_set(self.config, b"root", value.type.type,
                             value.value)

    def __setitem__(self, key: str, value: Value):
        lib.irmin_config_set(self.config, str.encode(key), value.type.type,
                             value.value)

    def __del__(self):
        lib.irmin_config_free(self.config)


class Repo:
    def __init__(self, config: Config):
        self.config = config
        self.repo = lib.irmin_repo_new(self.schema.schema, self.config.config)

    @property
    def schema(self) -> Schema:
        return self.config.schema

    def __del__(self):
        lib.irmin_repo_free(self.repo)


class Path:
    def __init__(self, schema: Schema, *args: str):
        a = [
            ffi.new("char[" + str(len(arg)) + "]", str.encode(arg))
            for arg in args
        ]
        a.append(ffi.NULL)
        d = ffi.new("char*[]", a)
        self.path = lib.irmin_path(schema.schema, d)

    def __del__(self):
        lib.irmin_path_free(self.path)


class Hash:
    def __init__(self, schema: Schema, h):
        self.schema = schema
        self.hash = h

    def __bytes__(self):
        s = lib.irmin_hash_get_string(self.schema.schema, self.hash)
        st = ffi.string(s)
        lib.free(s)
        return st

    def __str__(self):
        return bytes.decode(self.__bytes__())

    def __del__(self):
        lib.irmin_hash_free(self.hash)


class Info:
    def __init__(self, schema: Schema, i):
        self.schema = schema
        self.info = i

    @staticmethod
    def new(schema, author, message):
        return Info(
            schema,
            lib.irmin_info_new(schema.schema, str.encode(author),
                               str.encode(message)))

    @property
    def date(self) -> int:
        return lib.irmin_info_date(self.schema.schema, self.info)


class Commit:
    def __init__(self, schema: Schema, c):
        self.schema = schema
        self.commit = c

    @property
    def hash(self) -> Hash:
        h = lib.irmin_commit_hash(self.schema.schema, self.commit)
        return Hash(self.schema, h)

    @staticmethod
    def of_hash(repo: Repo, hash: Hash) -> Optional['Commit']:
        c = lib.irmin_commit_of_hash(hash.schema.schema, repo.repo, hash.hash)
        if c == ffi.NULL:
            return None
        return Commit(repo.schema, c)

    @property
    def parents(self) -> List['Commit']:
        n = lib.irmin_commit_parents_length(self.schema.schema, self.commit)
        d = [
            Commit(self.schema,
                   lib.irmin_commit_parent(self.schema.schema, self.commit, i))
            for i in range(n)
        ]
        return d

    def __del__(self):
        lib.irmin_commit_free(self.commit)

    def __str__(self):
        return self.hash.__str__()


class Tree:
    def __init__(self, schema: Schema, t=None):
        self.schema = schema
        if t is not None:
            self.tree = t
        else:
            self.tree = lib.irmin_tree_new(schema.schema)

    def add(self, k: Sequence[str], v) -> 'Tree':
        path = Path(self.schema, *k)
        value = self.schema.contents.f(v)
        lib.irmin_tree_add(self.schema.schema, path.path, value.value)
        return self

    def mem(self, k: Sequence[str]) -> bool:
        path = Path(self.schema, *k)
        return lib.irmin_tree_mem(self.schema.schema, path.path)


class Store:
    def __init__(self, repo: Repo, branch: str = "main"):
        self.repo = repo
        self.store = lib.irmin_of_branch(self.schema.schema, self.repo.repo,
                                         str.encode(branch))

    @property
    def schema(self) -> Schema:
        return self.repo.schema

    def __del__(self):
        lib.irmin_free(self.store)

    def __getitem__(self, key: Sequence[str]):
        path = Path(self.repo.config.schema, *key)
        x = lib.irmin_get(self.store, path.path)
        if x == ffi.NULL:
            return None
        return Value(x, self.schema.contents.type)

    def __setitem__(self, key: Sequence[str], value):
        return self.set(key, value)

    def set(self,
            key: Sequence[str],
            value,
            info: Optional[Info] = None) -> bool:
        path = Path(self.repo.config.schema, *key)
        value = self.schema.contents.f(value)
        info = lib.irmin_info_new(self.repo.config.schema.schema, b"irmin",
                                  b"set")
        x = lib.irmin_set(self.store, path.path, value.value, info)
        lib.irmin_info_free(info)
        return x

    @property
    def head(self) -> Optional[Commit]:
        c = lib.irmin_get_head(self.store)
        if c == ffi.NULL:
            return None
        return Commit(self.schema, c)

    def revert(self, c: Commit):
        lib.irmin_set_head(self.store, c.commit)
