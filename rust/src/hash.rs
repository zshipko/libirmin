use crate::internal::*;

pub struct Hash {
    pub ptr: *mut IrminHash,
}

impl Drop for Hash {
    fn drop(&mut self) {
        unsafe { irmin_hash_free(self.ptr) }
    }
}
