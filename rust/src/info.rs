use crate::internal::*;

pub struct Info<'a> {
    pub ptr: *mut IrminInfo,
    pub(crate) repo_ptr: *mut IrminRepo,
    pub(crate) _t: std::marker::PhantomData<&'a ()>,
}

impl<'a> Info<'a> {
    pub fn new<T: Contents>(
        repo: &Repo<T>,
        author: impl AsRef<str>,
        message: impl AsRef<str>,
    ) -> Result<Info, Error> {
        let message = cstring(message);
        let author = cstring(author);
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

        Ok(Info {
            ptr,
            repo_ptr: repo.ptr,
            _t: std::marker::PhantomData,
        })
    }

    pub fn date(&self) -> i64 {
        unsafe { irmin_info_date(self.repo_ptr, self.ptr) }
    }

    pub fn author(&self) -> Result<IrminString, Error> {
        let mut len = 0;
        let ptr = unsafe { irmin_info_author(self.repo_ptr, self.ptr, &mut len) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(IrminString(ptr, len))
    }

    pub fn message(&self) -> Result<IrminString, Error> {
        let mut len = 0;
        let ptr = unsafe { irmin_info_message(self.repo_ptr, self.ptr, &mut len) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(IrminString(ptr, len))
    }
}

impl<'a> Drop for Info<'a> {
    fn drop(&mut self) {
        unsafe { irmin_info_free(self.ptr) }
    }
}
