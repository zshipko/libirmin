use crate::internal::*;

pub struct Path<'a> {
    pub ptr: *mut IrminPath,
    repo: UntypedRepo<'a>,
}

impl<'a> Path<'a> {
    pub fn new<T: Contents>(repo: &'a Repo<T>, s: impl AsRef<str>) -> Result<Path, Error> {
        unsafe {
            let s = s.as_ref();
            let ptr = irmin_path_of_string(repo.ptr, s.as_ptr() as *mut _, s.len() as i32);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }
            Ok(Path {
                ptr,
                repo: UntypedRepo::new(repo),
            })
        }
    }

    pub fn parent(&self) -> Option<Path<'a>> {
        let ptr = unsafe { irmin_path_parent(self.repo.ptr, self.ptr) };
        if ptr.is_null() {
            return None;
        }
        Some(Path {
            ptr,
            repo: self.repo.clone(),
        })
    }

    pub fn append(&self, s: impl AsRef<str>) -> Result<Path<'a>, Error> {
        let s = s.as_ref();
        let ptr = unsafe {
            irmin_path_append(
                self.repo.ptr,
                self.ptr,
                s.as_ptr() as *mut _,
                s.len() as i32,
            )
        };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Path {
            ptr,

            repo: self.repo.clone(),
        })
    }

    pub fn to_string(&self) -> String {
        let mut len = 0i32;
        let ptr = unsafe { irmin_path_to_string(self.repo.ptr, self.ptr, &mut len) };
        if ptr.is_null() {
            return String::new();
        }
        let s = IrminString(ptr, len);
        s.into()
    }
}

impl<'a> Drop for Path<'a> {
    fn drop(&mut self) {
        unsafe { irmin_path_free(self.ptr) }
    }
}
