use crate::internal::*;

pub struct Value {
    pub ptr: *mut IrminValue,
}

impl Drop for Value {
    fn drop(&mut self) {
        unsafe { irmin_value_free(self.ptr) }
    }
}

impl Value {
    pub fn string(s: impl AsRef<str>) -> Result<Value, Error> {
        let s = s.as_ref();

        let ptr = unsafe { irmin_value_string(s.as_ptr() as *mut _, s.len() as i32) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }

        Ok(Value { ptr })
    }

    pub fn get_string(&self) -> Result<IrminString, Error> {
        unsafe {
            let len = &mut [0];
            let s = irmin_value_get_string(self.ptr, len.as_mut_ptr());
            if s.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(IrminString(s, len[0]))
        }
    }
}
