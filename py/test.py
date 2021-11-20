from irmin import Config, Store, Commit, Repo, Type, Hash, log_level

log_level("error")

config = Config.git(contents='json')
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
    assert (Hash.of_string(repo, str(head.hash)) == head.hash)
    print(Commit.of_hash(repo, head.hash))

assert (store.mem_tree(["test"]))
assert (Type.string().name == "string")

t = store.tree(["test"])
if t is not None:
    t["b"] = {"y": 0}
    print(t.to_dict())
    store.set_tree(["test"], t)

assert (["test", "a"] in store)
assert (["test", "b"] in store)
