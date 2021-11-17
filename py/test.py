from irmin import Config, Store, Commit, Repo

config = Config(backend='git', contents='json')
config.root("./test3")
repo = Repo(config)
store = Store(repo)
store["test", "a"] = {"x": "cool"}
c = store.head
store["test", "a"] = {"x": "ok"}
d = store.head
if d is not None:
    print(d.parents)
print(store["test", "a"])
if c is not None:
    store.revert(c)
print(store["test", "a"])
head = store.head
if head is not None:
    print(head.hash)
    print(Commit.of_hash(repo, head.hash))
