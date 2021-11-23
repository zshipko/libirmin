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
        let branch = format!("{}\0", branch.as_ref());
        unsafe {
            let ptr = irmin_of_branch(repo.ptr, branch.as_ptr() as *mut _);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Store { ptr, repo })
        }
    }

    pub fn set(&self, path: &Path, value: &T, info: Info) -> Result<bool, Error> {
        let value = value.to_value()?;
        unsafe {
            let r = irmin_set(self.ptr, path.ptr, value.ptr, info.ptr);
            Ok(r)
        }
    }

    pub fn set_tree(&self, path: &Path, tree: &Tree<T>, info: Info) -> Result<bool, Error> {
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

    pub fn find_tree(&mut self, path: &Path) -> Result<Option<Tree<T>>, Error> {
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

    pub fn mem(&mut self, path: &Path) -> bool {
        unsafe { irmin_mem(self.ptr, path.ptr) }
    }

    pub fn mem_tree(&mut self, path: &Path) -> bool {
        unsafe { irmin_mem_tree(self.ptr, path.ptr) }
    }

    pub fn remove(&mut self, path: &Path, info: Info) {
        unsafe { irmin_remove(self.ptr, path.ptr, info.ptr) }
    }
}

impl<'a, T: Contents> Drop for Store<'a, T> {
    fn drop(&mut self) {
        unsafe { irmin_free(self.ptr) }
    }
}
