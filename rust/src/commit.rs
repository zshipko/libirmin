use crate::internal::*;

pub struct Commit {
    pub ptr: *mut IrminCommit,
}

impl Drop for Commit {
    fn drop(&mut self) {
        unsafe { irmin_commit_free(self.ptr) }
    }
}
