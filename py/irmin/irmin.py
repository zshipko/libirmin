from _irmin_ffi import ffi, lib  # type: ignore
from typing import Optional, Sequence, Any, List, Union
import json

PathType = Union['Path', Sequence[str]]


class Type:
    def __init__(self, ptr):
        self._type = ptr

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

    @staticmethod
    def path(schema) -> 'Type':
        return Type(lib.irmin_type_path(schema._schema))

    def __del__(self):
        lib.irmin_type_free(self._type)


class Value:
    def __init__(self, ptr, ty: Type):
        self.type = ty
        self._value = ptr

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
        return Value(lib.irmin_value_of_string(t._type, s, len(s)), t)

    @staticmethod
    def json_value(d: Any) -> 'Value':
        t = Type.json_value()
        s = str.encode(json.dumps(d))
        return Value(lib.irmin_value_of_string(t._type, s, len(s)), t)

    def get_string(self) -> str:
        s = lib.irmin_value_get_string(self._value, ffi.NULL)
        st = ffi.string(s)
        lib.free(s)
        return bytes.decode(st)

    def to_bin(self) -> str:
        s = lib.irmin_value_to_bin(self._value, ffi.NULL)
        st = ffi.string(s)
        lib.free(s)
        return st

    @staticmethod
    def from_bin(t: Type, b: bytes) -> Optional['Value']:
        v = lib.irmin_value_of_bin(t._type, b, len(b))
        if v == ffi.NULL:
            return None
        return Value(v, t)

    def to_string(self) -> str:
        s = lib.irmin_value_to_string(self._value, ffi.NULL)
        st = ffi.string(s)
        lib.free(s)
        return st

    @staticmethod
    def from_string(t: Type, b: bytes) -> Optional['Value']:
        v = lib.irmin_value_of_string(t._type, b, len(b))
        if v == ffi.NULL:
            return None
        return Value(v, t)

    def __bytes__(self):
        s = lib.irmin_value_to_string(self.type._type, self._value, ffi.NULL)
        st = ffi.string(s)
        lib.free(s)
        return st

    def __str__(self):
        return bytes.decode(self.__bytes__())

    def __del__(self):
        lib.irmin_value_free(self._value)


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
        self.contents = self.content_types[c]
        self._schema = ptr

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
        lib.irmin_schema_free(self._schema)


class Config:
    def __init__(self, backend: Union[str, Schema], *args, **kwargs):
        if isinstance(backend, str):
            f = getattr(Schema, backend)
            self.schema = f(*args, **kwargs)
        else:
            self.schema = backend
        self._config = lib.irmin_config_new(self.schema._schema)

    def root(self, root: str):
        value = Value.string(root)
        lib.irmin_config_set(self._config, b"root", value.type._type,
                             value._value)

    def __setitem__(self, key: str, value: Value):
        lib.irmin_config_set(self._config, str.encode(key), value.type._type,
                             value._value)

    def __del__(self):
        lib.irmin_config_free(self._config)


class Repo:
    def __init__(self, config: Config):
        self.config = config
        self._repo = lib.irmin_repo_new(self.schema._schema,
                                        self.config._config)

    @property
    def schema(self) -> Schema:
        return self.config.schema

    def __del__(self):
        lib.irmin_repo_free(self._repo)


class Path:
    def __init__(self, schema: Schema, *args: str):
        a = [
            ffi.new("char[" + str(len(arg)) + "]", str.encode(arg))
            for arg in args
        ]
        a.append(ffi.NULL)
        d = ffi.new("char*[]", a)
        self._path = lib.irmin_path(schema._schema, d)

    @staticmethod
    def wrap(schema: Schema, path: PathType) -> 'Path':
        if isinstance(path, Path):
            return path
        return Path(schema, *path)

    @staticmethod
    def from_string(schema: Schema, s: str) -> Optional['Path']:
        t = Type.path(schema)
        b = str.encode(s)
        v = lib.irmin_value_of_string(t._type, b, len(b))
        if v == ffi.NULL:
            return None
        return Path(schema, v)

    def __str__(self):
        return Value(self._path, Type.path(self.schema)).to_string()

    def __del__(self):
        lib.irmin_path_free(self._path)


class Hash:
    def __init__(self, schema: Schema, h):
        self.schema = schema
        self._hash = h

    def __bytes__(self):
        s = lib.irmin_hash_get_string(self.schema._schema, self._hash)
        st = ffi.string(s)
        lib.free(s)
        return st

    def __str__(self):
        return bytes.decode(self.__bytes__())

    def __del__(self):
        lib.irmin_hash_free(self._hash)


class Info:
    def __init__(self, schema: Schema, i):
        self.schema = schema
        self._info = i

    @staticmethod
    def new(schema, author, message):
        return Info(
            schema,
            lib.irmin_info_new(schema._schema, str.encode(author),
                               str.encode(message)))

    @property
    def date(self) -> int:
        return lib.irmin_info_date(self.schema._schema, self._info)

    @property
    def author(self) -> str:
        s = lib.irmin_info_author(self.schema._schema, self._info)
        st = ffi.string(s)
        ffi.free(s)
        return bytes.decode(st)

    @property
    def message(self) -> str:
        s = lib.irmin_info_message(self.schema._schema, self._info)
        st = ffi.string(s)
        ffi.free(s)
        return bytes.decode(st)


class Commit:
    def __init__(self, schema: Schema, c):
        self.schema = schema
        self._commit = c

    @property
    def hash(self) -> Hash:
        h = lib.irmin_commit_hash(self.schema._schema, self._commit)
        return Hash(self.schema, h)

    @staticmethod
    def of_hash(repo: Repo, hash: Hash) -> Optional['Commit']:
        c = lib.irmin_commit_of_hash(hash.schema._schema, repo._repo,
                                     hash._hash)
        if c == ffi.NULL:
            return None
        return Commit(repo.schema, c)

    @property
    def parents(self) -> List['Commit']:
        n = lib.irmin_commit_parents_length(self.schema._schema, self._commit)
        d = [
            Commit(
                self.schema,
                lib.irmin_commit_parent(self.schema._schema, self._commit, i))
            for i in range(n)
        ]
        return d

    def __del__(self):
        lib.irmin_commit_free(self._commit)

    def __str__(self):
        return self.hash.__str__()


class Tree:
    def __init__(self, schema: Schema, t=None):
        self.schema = schema
        if t is not None:
            self._tree = t
        else:
            self._tree = lib.irmin_tree_new(schema._schema)

    def __setitem__(self, path: PathType, v) -> bool:
        path = Path.wrap(self.schema, path)
        if isinstance(v, Tree):
            return self.set_tree(path, v)
        value = self.schema.contents.f(v)
        return lib.irmin_tree_add(self.schema._schema, self._tree, path._path,
                                  value._value)

    def __getitem__(self, path: PathType, v) -> Optional['Value']:
        path = Path.wrap(self.schema, path)
        v = lib.irmin_tree_find(self.schema._schema, self._tree, path._path)
        if v == ffi.NULL:
            return None
        return Value(v, self.schema.contents.type)

    def __delitem__(self, path: PathType):
        path = Path.wrap(self.schema, path)
        ffi.irmin_tree_remove(self.schema._schema, self._tree, path._path)

    def __contains__(self, path: PathType) -> bool:
        path = Path.wrap(self.schema, path)
        return lib.irmin_tree_mem(self.schema._schema, self._tree, path._path)

    def mem_tree(self, path: PathType) -> bool:
        path = Path.wrap(self.schema, path)
        return lib.irmin_tree_mem_tree(self.schema._schema, self._tree,
                                       path._path)

    def tree(self, path: PathType):
        path = Path.wrap(self.schema, path)
        x = lib.irmin_tree_get_tree(self.schema._schema, self._tree,
                                    path._path)
        if x == ffi.NULL:
            return None
        return Tree(self.schema, x)

    def set_tree(self, path: PathType, tree: 'Tree') -> bool:
        path = Path.wrap(self.schema, path)
        x = lib.irmin_tree_set_tree(self.schema._schema, self._tree,
                                    path._path, tree._tree)
        return x


class Store:
    def __init__(self, repo: Repo, branch: str = "main"):
        self.repo = repo
        self._store = lib.irmin_of_branch(self.schema._schema, self.repo._repo,
                                          str.encode(branch))

    @property
    def schema(self) -> Schema:
        return self.repo.schema

    def __del__(self):
        lib.irmin_free(self._store)

    def __getitem__(self, path: PathType):
        path = Path.wrap(self.schema, path)
        x = lib.irmin_get(self._store, path._path)
        if x == ffi.NULL:
            return None
        return Value(x, self.schema.contents.type)

    def tree(self, path: PathType):
        path = Path.wrap(self.schema, path)
        x = lib.irmin_get_tree(self._store, path._path)
        if x == ffi.NULL:
            return None
        return Tree(self.schema, x)

    def __setitem__(self, path: PathType, value):
        if isinstance(value, Tree):
            return self.set_tree(path, value)
        return self.set(path, value)

    def __delitem__(self, path: PathType):
        path = Path.wrap(self.schema, path)
        ffi.irmin_remove(self._store, path._path)

    def __contains__(self, path: PathType) -> bool:
        path = Path.wrap(self.schema, path)
        return lib.irmin_mem(self._store, path._path)

    def info(self, author: str = "", message: str = "") -> Info:
        return Info.new(self.schema, author, message)

    def set(self, path: PathType, value, info: Optional[Info] = None) -> bool:
        path = Path.wrap(self.schema, path)
        value = self.schema.contents.f(value)
        if info is None:
            info = self.info("irmin", "set")
        x = lib.irmin_set(self._store, path._path, value._value, info._info)
        return x

    def set_tree(self,
                 path: PathType,
                 tree: Tree,
                 info: Optional[Info] = None) -> bool:
        path = Path.wrap(self.schema, path)
        if info is None:
            info = self.info("irmin", "set_tree")
        x = lib.irmin_set_tree(self._store, path._path, tree._tree, info._info)
        return x

    def mem_tree(self, path: PathType) -> bool:
        path = Path.wrap(self.schema, path)
        return lib.irmin_mem_tree(self._store, path._path)

    @property
    def head(self) -> Optional[Commit]:
        c = lib.irmin_get_head(self._store)
        if c == ffi.NULL:
            return None
        return Commit(self.schema, c)

    def revert(self, c: Commit):
        lib.irmin_set_head(self._store, c._commit)

    def fast_forward(self, c: Commit, info: Optional[Info] = None) -> bool:
        if info is None:
            info = self.info("irmin", "fast forward")
        return lib.irmin_fast_forward(self._store, c._commit, info._info)

    def merge_with_branch(self, branch: str, info: Optional[Info] = None):
        if info is None:
            info = self.info("irmin", "merge")
        lib.irmin_merge_with_branch(self._store, str.encode(branch),
                                    info._info)

    def merge_with_commit(self, commit: Commit, info: Optional[Info] = None):
        if info is None:
            info = self.info("irmin", "merge commit")
        lib.irmin_merge_with_branch(self._store, commit._commit, info._info)
