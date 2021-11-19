from irmin import Config, Store, Commit, Repo, log_level

log_level("debug")

# TODO: track down why irmin-git crashes here:
# config = Config.git(contents='string')

config = Config.pack(contents='string')
config.root("./test3")
repo = Repo(config)
store = Store(repo)
store["test", "a"] = "cool"  # {"x": "cool"}
c = store.head
store["test", "a"] = "ok"  # {"x": "ok"}
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

assert (store.mem_tree(["test"]))

t = store.tree(["test"])
if t is not None:
    t["b"] = "abc"  # {"y": 0}
    store.set_tree(["test"], t)

assert (["test", "a"] in store)
assert (["test", "b"] in store)
