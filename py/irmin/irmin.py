from .irmin_ffi import ffi, lib  # type: ignore

from typing import Optional, Sequence, Any, List, Union
import json

PathType = Union['Path', str, Sequence[str]]


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
    def path(repo) -> 'Type':
        return Type(lib.irmin_type_path(repo._repo))

    @staticmethod
    def hash(repo) -> 'Type':
        return Type(lib.irmin_type_hash(repo._repo))

    @staticmethod
    def tree(repo) -> 'Type':
        return Type(lib.irmin_type_tree(repo._repo))

    @staticmethod
    def commit(repo) -> 'Type':
        return Type(lib.irmin_type_commit(repo._repo))

    @property
    def name(self) -> str:
        s = lib.irmin_type_name(self._type, ffi.NULL)
        st = ffi.string(s)
        lib.free(s)
        return bytes.decode(st)

    def __str__(self):
        return self.name()

    def __eq__(self, other: 'Type') -> bool:  # type: ignore
        return self.name == other.name

    def __del__(self):
        lib.irmin_type_free(self._type)


class Value:
    def __init__(self, ptr, ty: Type):
        self.type = ty
        self._value = ptr

    def __eq__(self, other: 'Value') -> bool:  # type: ignore
        return lib.irmin_value_equal(self.type._type, self._value,
                                     other._value)

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
        n = ffi.new("int[1]", [0])
        s = lib.irmin_value_get_string(self._value, n)
        st = ffi.string(s, n[0])
        lib.free(s)
        return bytes.decode(st)

    def to_bin(self) -> bytes:
        n = ffi.new("int[1]", [0])
        s = lib.irmin_value_to_bin(self._value, n)
        st = ffi.string(s, n[0])
        lib.free(s)
        return st

    @staticmethod
    def of_bin(t: Type, b: bytes) -> Optional['Value']:
        v = lib.irmin_value_of_bin(t._type, b, len(b))
        if v == ffi.NULL:
            return None
        return Value(v, t)

    def to_string(self) -> str:
        n = ffi.new("int[1]", [0])
        s = lib.irmin_value_to_string(self._value, n)
        st = ffi.string(s, n[0])
        lib.free(s)
        return st

    @staticmethod
    def of_string(t: Type, b: bytes) -> Optional['Value']:
        v = lib.irmin_value_of_string(t._type, b, len(b))
        if v == ffi.NULL:
            return None
        return Value(v, t)

    def __bytes__(self):
        n = ffi.new("int[1]", [0])
        s = lib.irmin_value_to_string(self.type._type, self._value, n)
        st = ffi.string(s, n[0])
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


content_types = {
    "string": Contents(Value.string, Type.string(), str),
    "json": Contents(Value.json, Type.json(), dict),
    "json-value": Contents(Value.json_value, Type.json_value(), Any)
}


def log_level(level):
    if level is None:
        lib.irmin_log_level(ffi.NULL)
    else:
        lib.irmin_log_level(str.encode(level))


class Config:
    def __init__(self, ptr, contents="string", *args, **kwargs):
        self._config = ptr
        self.contents = content_types[contents]

    def root(self, root: str):
        value = Value.string(root)
        lib.irmin_config_set(self._config, b"root", value.type._type,
                             value._value)

    def __setitem__(self, key: str, value: Value):
        lib.irmin_config_set(self._config, str.encode(key), value.type._type,
                             value._value)

    def __del__(self):
        lib.irmin_config_free(self._config)

    @staticmethod
    def git(contents="string"):
        return Config(lib.irmin_config_git(str.encode(contents)),
                      contents=contents)

    @staticmethod
    def git_mem(contents="string"):
        return Config(lib.irmin_config_git_mem(str.encode(contents)),
                      contents=contents)

    @staticmethod
    def pack(contents="string", hash: Optional[str] = None):
        h = ffi.NULL if hash is None else str.encode(hash)
        return Config(lib.irmin_config_pack(h, str.encode(contents)),
                      contents=contents)

    @staticmethod
    def mem(contents="string", hash: Optional[str] = None):
        h = ffi.NULL if hash is None else str.encode(hash)
        return Config(lib.irmin_config_mem(h, str.encode(contents)),
                      contents=contents)

    @staticmethod
    def fs(contents="string", hash: Optional[str] = None):
        h = ffi.NULL if hash is None else str.encode(hash)
        return Config(lib.irmin_config_fs(h, str.encode(contents)),
                      contents=contents)


class Repo:
    def __init__(self, config: Config):
        self.config = config
        self._repo = lib.irmin_repo_new(self.config._config)

    def __del__(self):
        lib.irmin_repo_free(self._repo)


class Path:
    def __init__(self, repo: Repo, ptr):
        self.repo = repo
        if isinstance(ptr, (tuple, list)):
            a = [ffi.new("char[]", str.encode(arg)) for arg in ptr]
            a.append(ffi.NULL)
            x = ffi.new("char*[]", a)
            ptr = lib.irmin_path(self.repo._repo, x)
        self._path = ptr

    def __eq__(self, other: 'Path') -> bool:  # type: ignore
        return lib.irmin_path_equal(self.repo._repo, self._path, other._path)

    @staticmethod
    def wrap(repo: Repo, path: PathType) -> 'Path':
        if isinstance(path, Path):
            return path
        elif isinstance(path, str):
            return Path(repo, [path])
        return Path(repo, path)

    @staticmethod
    def of_string(repo: Repo, s: str) -> Optional['Path']:
        b = str.encode(s)
        v = lib.irmin_path_of_string(repo._repo, b, len(b))
        if v == ffi.NULL:
            return None
        return Path(repo, v)

    def __str__(self):
        b = lib.irmin_path_to_string(self.repo._repo, self._path)
        return bytes.decode(b)

    def __del__(self):
        lib.irmin_path_free(self._path)


class Hash:
    def __init__(self, repo: Repo, h):
        self.repo = repo
        self._hash = h

    def __eq__(self, other: 'Hash') -> bool:  # type: ignore
        return lib.irmin_hash_equal(self.repo._repo, self._hash, other._hash)

    def __bytes__(self):
        n = ffi.new("int[1]", [0])
        s = lib.irmin_hash_to_string(self.repo._repo, self._hash, n)
        st = ffi.string(s, n[0])
        lib.free(s)
        return st

    @staticmethod
    def of_string(repo, s):
        b = str.encode(s)
        h = lib.irmin_hash_of_string(repo._repo, b, len(b))
        return Hash(repo, h)

    def __str__(self):
        return bytes.decode(self.__bytes__())

    def __del__(self):
        lib.irmin_hash_free(self._hash)


class Info:
    def __init__(self, repo: Repo, i):
        self.repo = repo
        self._info = i

    @staticmethod
    def new(repo, author, message):
        return Info(
            repo,
            lib.irmin_info_new(repo._repo, str.encode(author),
                               str.encode(message)))

    @property
    def date(self) -> int:
        return lib.irmin_info_date(self.repo._repo, self._info)

    @property
    def author(self) -> str:
        s = lib.irmin_info_author(self.repo._repo, self._info)
        st = ffi.string(s)
        lib.free(s)
        return bytes.decode(st)

    @property
    def message(self) -> str:
        s = lib.irmin_info_message(self.repo._repo, self._info)
        st = ffi.string(s)
        lib.free(s)
        return bytes.decode(st)

    def __del__(self):
        lib.irmin_info_free(self._info)


class Commit:
    def __init__(self, repo: Repo, c):
        self.repo = repo
        self._commit = c

    @property
    def hash(self) -> Hash:
        h = lib.irmin_commit_hash(self.repo._repo, self._commit)
        return Hash(self.repo, h)

    def __eq__(self, other: 'Commit') -> bool:  # type: ignore
        return lib.irmin_commit_equal(self.repo._repo, self._commit,
                                      other._commit)

    @staticmethod
    def of_hash(repo: Repo, hash: Hash) -> Optional['Commit']:
        c = lib.irmin_commit_of_hash(repo._repo, hash._hash)
        if c == ffi.NULL:
            return None
        return Commit(repo, c)

    @property
    def parents(self) -> List['Commit']:
        n = lib.irmin_commit_parents_length(self.repo._repo, self._commit)
        d = [
            Commit(self.repo,
                   lib.irmin_commit_parent(self.repo._repo, self._commit, i))
            for i in range(n)
        ]
        return d

    def __del__(self):
        lib.irmin_commit_free(self._commit)

    def __str__(self):
        return self.hash.__str__()


class Tree:
    def __init__(self, repo: Repo, t=None):
        self.repo = repo
        if t is not None:
            self._tree = t
        else:
            self._tree = lib.irmin_tree_new(self.repo._repo)

    def __eq__(self, other: 'Tree') -> bool:  # type: ignore
        return lib.irmin_tree_equal(self.repo._repo, self._tree, other._tree)

    def __setitem__(self, path: PathType, v):
        if isinstance(v, Tree):
            return self.set_tree(path, v)

        path = Path.wrap(self.repo, path)
        value = self.repo.config.contents.f(v)
        lib.irmin_tree_add(self.repo._repo, self._tree, path._path,
                           value._value)

    def __getitem__(self, path: PathType) -> Optional['Value']:
        path = Path.wrap(self.repo, path)
        v = lib.irmin_tree_find(self.repo._repo, self._tree, path._path)
        if v == ffi.NULL:
            return None
        return Value(v, self.repo.config.contents.type)

    def __delitem__(self, path: PathType):
        path = Path.wrap(self.repo, path)
        ffi.irmin_tree_remove(self.repo._repo, self._tree, path._path)

    def __contains__(self, path: PathType) -> bool:
        path = Path.wrap(self.repo, path)
        return lib.irmin_tree_mem(self.repo._repo, self._tree, path._path)

    def mem_tree(self, path: PathType) -> bool:
        path = Path.wrap(self.repo, path)
        return lib.irmin_tree_mem_tree(self.repo._repo, self._tree, path._path)

    def tree(self, path: PathType):
        path = Path.wrap(self.repo, path)
        x = lib.irmin_tree_find_tree(self.repo._repo, self._tree, path._path)
        if x == ffi.NULL:
            return None
        return Tree(self.repo, x)

    def set_tree(self, path: PathType, tree: 'Tree'):
        path = Path.wrap(self.repo, path)
        lib.irmin_tree_set_tree(self.repo._repo, self._tree, path._path,
                                tree._tree)

    def __del__(self):
        lib.irmin_tree_free(self._tree)


class Store:
    def __init__(self, repo: Repo, branch: str = "main"):
        self.repo = repo
        self._store = lib.irmin_of_branch(self.repo._repo, str.encode(branch))

    def __del__(self):
        lib.irmin_free(self._store)

    def __getitem__(self, path: PathType):
        path = Path.wrap(self.repo, path)
        x = lib.irmin_find(self._store, path._path)
        if x == ffi.NULL:
            return None
        return Value(x, self.repo.config.contents.type)

    def tree(self, path: PathType):
        path = Path.wrap(self.repo, path)
        x = lib.irmin_find_tree(self._store, path._path)
        if x == ffi.NULL:
            return None
        return Tree(self.repo, x)

    def __setitem__(self, path: PathType, value):
        if isinstance(value, Tree):
            return self.set_tree(path, value)
        return self.set(path, value)

    def __delitem__(self, path: PathType):
        path = Path.wrap(self.repo, path)
        ffi.irmin_remove(self._store, path._path)

    def __contains__(self, path: PathType) -> bool:
        path = Path.wrap(self.repo, path)
        return lib.irmin_mem(self._store, path._path)

    def info(self, author: str = "", message: str = "") -> Info:
        return Info.new(self.repo, author, message)

    def set(self, path: PathType, value, info: Optional[Info] = None):
        path = Path.wrap(self.repo, path)
        value = self.repo.config.contents.f(value)
        if info is None:
            info = self.info("irmin", "set")
        lib.irmin_set(self._store, path._path, value._value, info._info)

    def set_tree(self,
                 path: PathType,
                 tree: Tree,
                 info: Optional[Info] = None):
        path = Path.wrap(self.repo, path)
        if info is None:
            info = self.info("irmin", "set_tree")
        lib.irmin_set_tree(self._store, path._path, tree._tree, info._info)

    def mem_tree(self, path: PathType) -> bool:
        path = Path.wrap(self.repo, path)
        return lib.irmin_mem_tree(self._store, path._path)

    @property
    def head(self) -> Optional[Commit]:
        c = lib.irmin_get_head(self._store)
        if c == ffi.NULL:
            return None
        return Commit(self.repo, c)

    def revert(self, c: Commit):
        lib.irmin_set_head(self._store, c._commit)

    def fast_forward(self, c: Commit, info: Optional[Info] = None) -> bool:
        if info is None:
            info = self.info("irmin", "fast forward")
        return lib.irmin_fast_forward(self._store, c._commit, info._info)

    def merge_with_branch(self,
                          branch: str,
                          info: Optional[Info] = None) -> bool:
        if info is None:
            info = self.info("irmin", "merge")
        return lib.irmin_merge_with_branch(self._store, str.encode(branch),
                                           info._info)

    def merge_with_commit(self,
                          commit: Commit,
                          info: Optional[Info] = None) -> bool:
        if info is None:
            info = self.info("irmin", "merge commit")
        return lib.irmin_merge_with_branch(self._store, commit._commit,
                                           info._info)
