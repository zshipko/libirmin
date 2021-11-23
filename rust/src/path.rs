use crate::internal::*;

pub struct Path {
    pub ptr: *mut IrminPath,
}

impl Path {
    pub fn new<T: Contents>(repo: &Repo<T>, s: impl AsRef<str>) -> Result<Path, Error> {
        unsafe {
            let s = s.as_ref();
            let ptr = irmin_path_of_string(repo.ptr, s.as_ptr() as *mut _, s.len() as i32);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }
            Ok(Path { ptr })
        }
    }
}

impl Drop for Path {
    fn drop(&mut self) {
        unsafe { irmin_path_free(self.ptr) }
    }
}
