use crate::internal::*;

pub struct Type {
    pub ptr: *mut IrminType,
}

impl Drop for Type {
    fn drop(&mut self) {
        unsafe { irmin_type_free(self.ptr) }
    }
}

impl Type {
    pub fn string() -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_string() };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }

    pub fn json() -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_json() };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }

    pub fn json_value() -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_json_value() };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }
}
