use crate::internal::*;

pub struct Hash<'a> {
    pub ptr: *mut IrminHash,
    pub(crate) repo: UntypedRepo<'a>,
}

impl<'a> Hash<'a> {
    pub fn of_string<T: Contents>(
        repo: &'a Repo<T>,
        s: impl AsRef<str>,
    ) -> Result<Hash<'a>, Error> {
        let s = s.as_ref();
        let ptr = unsafe { irmin_hash_of_string(repo.ptr, s.as_ptr() as *mut _, s.len() as i32) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Hash {
            ptr,
            repo: UntypedRepo::new(repo),
        })
    }

    pub fn to_string<T: Contents>(&self) -> String {
        let mut len = 0;
        let s = unsafe { irmin_hash_to_string(self.repo.ptr, self.ptr, &mut len) };
        if s.is_null() {
            return String::new();
        }
        IrminString(s, len).into()
    }
}

impl<'a> Drop for Hash<'a> {
    fn drop(&mut self) {
        unsafe { irmin_hash_free(self.ptr) }
    }
}
