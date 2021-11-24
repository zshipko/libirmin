use crate::internal::*;

pub struct Type {
    pub ptr: *mut IrminType,
}

impl Clone for Type {
    fn clone(&self) -> Type {
        let ptr = unsafe { irmin_value_make(self.ptr as *mut _) as *mut IrminType };
        Type { ptr }
    }
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

    pub fn int() -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_int() };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }

    pub fn float() -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_float() };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }

    pub fn bool() -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_bool() };
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

    pub fn path<T: Contents>(repo: &Repo<T>) -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_path(repo.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }

    pub fn hash<T: Contents>(repo: &Repo<T>) -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_hash(repo.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }

    pub fn commit<T: Contents>(repo: &Repo<T>) -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_commit(repo.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }

    pub fn tree<T: Contents>(repo: &Repo<T>) -> Result<Type, Error> {
        let ptr = unsafe { irmin_type_tree(repo.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Type { ptr })
    }

    pub fn name(&self) -> Result<IrminString, Error> {
        let mut len = 0;
        let name = unsafe { irmin_type_name(self.ptr, &mut len) };
        if name.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(IrminString(name, len))
    }
}
