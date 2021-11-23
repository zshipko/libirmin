use crate::internal::*;

pub struct Repo<T: Contents> {
    pub config: Config<T>,
    pub ptr: *mut IrminRepo,
}

impl<T: Contents> Repo<T> {
    pub fn new(config: Config<T>) -> Result<Repo<T>, Error> {
        unsafe {
            let ptr = irmin_repo_new(config.ptr);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Repo { config, ptr })
        }
    }

    pub fn path(&self, s: impl AsRef<str>) -> Result<Path, Error> {
        Path::new(self, s)
    }

    pub fn tree(&self) -> Result<Tree<T>, Error> {
        Tree::new(self)
    }
}

impl<T: Contents> Drop for Repo<T> {
    fn drop(&mut self) {
        unsafe { irmin_repo_free(self.ptr) }
    }
}
