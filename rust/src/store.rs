use crate::internal::*;

pub struct Store<'a, T: Contents> {
    pub ptr: *mut Irmin,
    pub repo: &'a Repo<T>,
}

impl<'a, T: Contents> Store<'a, T> {
    pub fn new(repo: &'a Repo<T>) -> Result<Store<'a, T>, Error> {
        unsafe {
            let ptr = irmin_main(repo.ptr);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Store { ptr, repo })
        }
    }

    pub fn of_branch(repo: &'a Repo<T>, branch: impl AsRef<str>) -> Result<Store<'a, T>, Error> {
        let branch = cstring(branch);
        unsafe {
            let ptr = irmin_of_branch(repo.ptr, branch.as_ptr() as *mut _);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Store { ptr, repo })
        }
    }

    pub fn set(&mut self, path: &Path, value: &T, info: Info) -> Result<bool, Error> {
        let value = value.to_value()?;
        unsafe {
            let r = irmin_set(self.ptr, path.ptr, value.ptr, info.ptr);
            Ok(r)
        }
    }

    pub fn set_tree(&mut self, path: &Path, tree: &Tree<T>, info: Info) -> Result<bool, Error> {
        unsafe {
            let r = irmin_set_tree(self.ptr, path.ptr, tree.ptr, info.ptr);
            Ok(r)
        }
    }

    pub fn find(&self, path: &Path) -> Result<Option<T>, Error> {
        let r = unsafe { irmin_find(self.ptr, path.ptr) };
        if r.is_null() {
            return Ok(None);
        }

        let ty = T::ty()?;
        let v = Value { ptr: r, ty };
        let v = T::from_value(&v)?;
        Ok(Some(v))
    }

    pub fn find_tree(&self, path: &Path) -> Result<Option<Tree<T>>, Error> {
        unsafe {
            let ptr = irmin_find_tree(self.ptr, path.ptr);
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

    pub fn mem(&self, path: &Path) -> bool {
        unsafe { irmin_mem(self.ptr, path.ptr) }
    }

    pub fn mem_tree(&self, path: &Path) -> bool {
        unsafe { irmin_mem_tree(self.ptr, path.ptr) }
    }

    pub fn remove(&mut self, path: &Path, info: Info) {
        unsafe { irmin_remove(self.ptr, path.ptr, info.ptr) }
    }

    pub fn head(&self) -> Option<Commit<'a>> {
        let ptr = unsafe { irmin_get_head(self.ptr) };
        if ptr.is_null() {
            return None;
        }

        Some(Commit {
            ptr,
            repo: UntypedRepo::new(&self.repo),
        })
    }

    pub fn set_head(&self, c: &Commit) {
        unsafe { irmin_set_head(self.ptr, c.ptr) }
    }

    pub fn fast_forward(&self, c: &Commit) -> bool {
        unsafe { irmin_fast_forward(self.ptr, c.ptr) }
    }

    pub fn merge_with_branch(&self, branch: impl AsRef<str>, info: Info) -> bool {
        let branch = cstring(branch);
        unsafe { irmin_merge_with_branch(self.ptr, branch.as_ptr() as *mut _, info.ptr) }
    }

    pub fn merge_with_commit(&self, commit: &Commit, info: Info) -> bool {
        unsafe { irmin_merge_with_commit(self.ptr, commit.ptr, info.ptr) }
    }
}

impl<'a, T: Contents> Drop for Store<'a, T> {
    fn drop(&mut self) {
        unsafe { irmin_free(self.ptr) }
    }
}
