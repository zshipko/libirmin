use crate::internal::*;

/// Wrapper around Irmin repo
pub struct Repo<T: Contents> {
    pub config: Config<T>,
    pub ptr: *mut IrminRepo,
}

impl<T: Contents> Repo<T> {
    /// Create a new repo from the given config
    pub fn new(config: Config<T>) -> Result<Repo<T>, Error> {
        unsafe {
            let ptr = irmin_repo_new(config.ptr);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Repo { config, ptr })
        }
    }
}

impl<T: Contents> Drop for Repo<T> {
    fn drop(&mut self) {
        unsafe { irmin_repo_free(self.ptr) }
    }
}
