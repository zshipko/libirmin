use crate::internal::*;

pub struct Info {
    pub ptr: *mut IrminInfo,
}

impl Info {
    pub fn new<T: Contents>(
        repo: &Repo<T>,
        author: impl AsRef<str>,
        message: impl AsRef<str>,
    ) -> Result<Info, Error> {
        let message = format!("{}\0", message.as_ref());
        let author = format!("{}\0", author.as_ref());
        let ptr = unsafe {
            irmin_info_new(
                repo.ptr,
                author.as_ptr() as *mut _,
                message.as_ptr() as *mut _,
            )
        };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }

        Ok(Info { ptr })
    }
}

impl Drop for Info {
    fn drop(&mut self) {
        unsafe { irmin_info_free(self.ptr) }
    }
}
