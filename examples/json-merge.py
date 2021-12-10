from util import *

# Configure an in-memory store with `json` contents
config = irmin.Config.mem(contents='json')

# Initialize the repo
repo = irmin.Repo(config)

# Open the store, if no branch is specified the `main` branch is used
store = irmin.Store(repo)

# This is the object that will be stored in Irmin
a = {'x': 1, 'y': 2, 'z': 3}

# Update the store
store['foo', 'bar'] = a

# Create a new branch called `branch1` and
# set its head to the latest commit on `main`
branch1 = irmin.Store(repo, 'branch1')
branch1.set_head(store.head)

# Create another new branch called `branch2`
branch2 = irmin.Store(repo, 'branch2')
branch2.set_head(store.head)

# Update `branch1`, setting `x` to 0
b = {'x': 0, 'y': 2, 'z': 3}
branch1['foo', 'bar'] = b

# Update `branch2`, setting `y` to 0
c = {'x': 1, 'y': 0, 'z': 3}
branch2['foo', 'bar'] = c

# Merge `branch1` into `main`
assert (store.merge(branch1))

# Merge `branch2` back into `main`
assert (store.merge(branch2))

# Check that the contents have been merged correctly, now
# `x` and `y` should both be set to 0 after being updated
# in separate branches
assert (store['foo', 'bar'] == {'x': 0, 'y': 0, 'z': 3})
