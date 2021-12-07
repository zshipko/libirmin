from irmin import Config, Store, Commit, Repo, Type, Hash, Value, log_level

log_level("error")


def init():
    config = Config.git_mem(contents='json')
    repo = Repo(config)
    return repo, Store(repo)


def test_irmin_type():
    assert (Type.string().name == "string")
    assert (Type.bool().name == "bool")
    assert (Type.string() == Type.string())
    assert (Type.unit() != Type.string())


def test_irmin_value():
    foo_a = Value.string("foo")
    foo_b = Value.string("foo")
    bar = Value.string("bar")
    assert (foo_a == foo_b)
    assert (foo_a != bar)

    a = Value.bool(True)
    s = Value.to_string(a)
    assert (s == "true")


def test_irmin_head():
    repo, store = init()
    store["test", "a"] = {"x": "cool"}
    c = store.head
    store["test", "a"] = {"x": "ok"}
    d = store.head
    if d is not None:
        print(d.parents)
    print(store["test", "a"])
    if c is not None:
        store.set_head(c)
    print(store["test", "a"])
    head = store.head
    if head is not None:
        assert (head.hash == c.hash)
        assert (Hash.of_string(repo, str(head.hash)) == head.hash)
        assert (Commit.of_hash(repo, head.hash) == c)


def test_tree():
    repo, store = init()
    store["a", "b", "c"] = {"foo": "bar"}

    assert (store.mem_tree(["a"]))

    t = store.tree(["a", "b"])
    if t is not None:
        assert (["c"] in t)
        assert (t["c"] == {"foo": "bar"})
        t["d"] = {"x": 0}
        store.set_tree(["a", "b"], t)

    assert (["a", "b", "c"] in store)
    assert (["a", "b", "d"] in store)

    assert (store["a", "b", "c"] == {"foo": "bar"})
    assert (store["a", "b", "d"] == {"x": 0})
