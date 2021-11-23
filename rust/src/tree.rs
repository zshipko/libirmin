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
}
