use crate::internal::*;

pub struct Tree<'a, T: Contents> {
    pub ptr: *mut IrminTree,
    pub repo: &'a Repo<T>,
}

impl<'a, T: Contents> Drop for Tree<'a, T> {
    fn drop(&mut self) {
        unsafe { irmin_tree_free(self.ptr) }
    }
}

impl<'a, T: Contents> Tree<'a, T> {
    pub fn new(repo: &'a Repo<T>) -> Result<Tree<'a, T>, Error> {
        unsafe {
            let ptr = irmin_tree_new(repo.ptr);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }
            Ok(Tree { ptr, repo })
        }
    }

    pub fn add(&mut self, path: &Path, value: &T) -> Result<(), Error> {
        unsafe {
            let value = value.to_value()?;
            irmin_tree_add(self.repo.ptr, self.ptr, path.ptr, value.ptr);
            Ok(())
        }
    }

    pub fn add_tree(&mut self, path: &Path, tree: &Tree<T>) {
        unsafe { irmin_tree_add_tree(self.repo.ptr, self.ptr, path.ptr, tree.ptr) }
    }

    pub fn mem(&self, path: &Path) -> bool {
        unsafe { irmin_tree_mem(self.repo.ptr, self.ptr, path.ptr) }
    }

    pub fn mem_tree(&self, path: &Path) -> bool {
        unsafe { irmin_tree_mem_tree(self.repo.ptr, self.ptr, path.ptr) }
    }

    pub fn remove(&mut self, path: &Path) {
        unsafe { irmin_tree_remove(self.repo.ptr, self.ptr, path.ptr) }
    }

    pub fn find(&self, path: &Path) -> Result<Option<T>, Error> {
        unsafe {
            let ptr = irmin_tree_find(self.repo.ptr, self.ptr, path.ptr);
            if ptr.is_null() {
                return Ok(None);
            }
            let ty = T::ty()?;
            let x = Value { ptr, ty };
            let value = T::from_value(&x)?;
            Ok(Some(value))
        }
    }

    pub fn find_tree(&self, path: &Path) -> Result<Option<Tree<T>>, Error> {
        unsafe {
            let ptr = irmin_tree_find_tree(self.repo.ptr, self.ptr, path.ptr);
            if ptr.is_null() {
                return Ok(None);
            }
            let x = Tree {
                ptr,
                repo: self.repo,
            };
            Ok(Some(x))
        }
    }
}
