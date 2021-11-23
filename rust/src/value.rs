use crate::internal::*;

pub struct Value {
    pub ty: Type,
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

        let ty = Type::string()?;

        Ok(Value { ptr, ty })
    }

    pub fn of_string(ty: Type, s: impl AsRef<str>) -> Result<Value, Error> {
        let s = s.as_ref();

        let ptr = unsafe { irmin_value_of_string(ty.ptr, s.as_ptr() as *mut _, s.len() as i32) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }

        Ok(Value { ptr, ty })
    }

    pub fn to_string(&self) -> Result<IrminString, Error> {
        let mut len = 0;
        let s = unsafe { irmin_value_to_string(self.ty.ptr, self.ptr, &mut len) };
        if s.is_null() {
            return Err(Error::NullPtr);
        }

        Ok(IrminString(s, len))
    }

    pub fn of_bin(ty: Type, s: impl AsRef<[u8]>) -> Result<Value, Error> {
        let s = s.as_ref();
        let ptr = unsafe { irmin_value_of_bin(ty.ptr, s.as_ptr() as *mut _, s.len() as i32) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }

        Ok(Value { ptr, ty })
    }

    pub fn to_bin(&self) -> Result<IrminString, Error> {
        let mut len = 0;
        let s = unsafe { irmin_value_to_bin(self.ty.ptr, self.ptr, &mut len) };
        if s.is_null() {
            return Err(Error::NullPtr);
        }

        Ok(IrminString(s, len))
    }

    pub fn get_string(&self) -> Result<IrminString, Error> {
        let mut len = 0;
        let s = unsafe { irmin_value_get_string(self.ptr, &mut len) };
        if s.is_null() {
            return Err(Error::NullPtr);
        }

        Ok(IrminString(s, len))
    }
}
