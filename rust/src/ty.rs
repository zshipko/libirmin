use crate::internal::*;

pub struct Type {
    pub ptr: *mut IrminType,
}

impl Drop for Type {
    fn drop(&mut self) {
        unsafe { irmin_type_free(self.ptr) }
    }
}
