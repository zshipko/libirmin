from util import *
from irmin import *
import sys

if len(sys.argv) < 2:
    print("usage: python3 tezos.py /path/to/tezos/context")
    sys.exit(0)

root = sys.argv[1]

config = Config.tezos()
print(sys.argv[1])
config.root(sys.argv[1])

repo = Repo(config)
store = Store(repo, branch="master")


def list_path(store, path):
    for k in store.list(path):
        p = path.append(k)
        if p in store:
            print(p)
        else:
            list_path(store, p)


list_path(store, ["data", "contracts"])
