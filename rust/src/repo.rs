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
            check!(ptr);
            Ok(Repo { config, ptr })
        }
    }

    pub fn branches(&self) -> Result<Vec<IrminString>, Error> {
        let b = unsafe { irmin_repo_branches(self.ptr) };
        check!(b);
        let mut dest = Vec::new();
        let n = unsafe { irmin_branch_list_length(b) };
        for i in 0..n {
            let p = unsafe { irmin_branch_list_get(b, i) };
            if let Ok(s) = IrminString::wrap(p) {
                dest.push(s);
            }
        }
        unsafe { irmin_branch_list_free(b) };
        Ok(dest)
    }
}

impl<T: Contents> Drop for Repo<T> {
    fn drop(&mut self) {
        unsafe { irmin_repo_free(self.ptr) }
    }
}
