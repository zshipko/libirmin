use crate::internal::*;

pub struct Config<T: Contents> {
    pub ptr: *mut IrminConfig,
    _t: std::marker::PhantomData<T>,
}

impl<T: Contents> Drop for Config<T> {
    fn drop(&mut self) {
        unsafe { irmin_config_free(self.ptr) }
    }
}

pub enum ContentType {
    String,
    Json,
    JsonValue,
}

const CONTENTS_STRING: &str = "string\0";

const CONTENTS_JSON: &str = "json\0";

const CONTENTS_JSON_VALUE: &str = "json-value\0";

pub trait Contents
where
    Self: Sized,
{
    fn content_type() -> ContentType;

    fn to_value(&self) -> Result<Value, Error>;
    fn from_value(v: &Value) -> Result<Self, Error>;

    fn ty() -> Result<Type, Error> {
        match Self::content_type() {
            ContentType::String => Type::string(),
            ContentType::Json => Type::json(),
            ContentType::JsonValue => Type::json_value(),
        }
    }
}

impl ContentType {
    fn ptr(c: Option<ContentType>) -> *const u8 {
        match c {
            Some(ContentType::String) => CONTENTS_STRING.as_ptr(),
            Some(ContentType::Json) => CONTENTS_JSON.as_ptr(),
            Some(ContentType::JsonValue) => CONTENTS_JSON_VALUE.as_ptr(),
            None => std::ptr::null(),
        }
    }
}

pub enum HashType {
    Sha1,
    Blake2b,
}

const HASH_SHA1: &str = "sha1\0";

const HASH_BLAKE2B: &str = "blake2b\0";

impl HashType {
    fn ptr(h: Option<HashType>) -> *const u8 {
        match h {
            Some(HashType::Sha1) => HASH_SHA1.as_ptr(),
            Some(HashType::Blake2b) => HASH_BLAKE2B.as_ptr(),
            None => std::ptr::null(),
        }
    }
}

impl Contents for IrminString {
    fn content_type() -> ContentType {
        ContentType::String
    }

    fn to_value(&self) -> Result<Value, Error> {
        Value::string(self)
    }

    fn from_value(v: &Value) -> Result<Self, Error> {
        v.get_string()
    }
}

impl Contents for String {
    fn content_type() -> ContentType {
        ContentType::String
    }

    fn to_value(&self) -> Result<Value, Error> {
        Value::string(self)
    }

    fn from_value(v: &Value) -> Result<Self, Error> {
        v.get_string().map(|x| x.into())
    }
}

impl Contents for serde_json::Value {
    fn content_type() -> ContentType {
        ContentType::JsonValue
    }

    fn to_value(&self) -> Result<Value, Error> {
        let ty = Type::json_value()?;
        let s = serde_json::to_string(self)?;
        Value::of_string(ty, s)
    }

    fn from_value(v: &Value) -> Result<Self, Error> {
        let s = v.to_string()?;
        serde_json::from_str(s.as_ref()).map_err(Error::from)
    }
}

impl Contents for serde_json::Map<String, serde_json::Value> {
    fn content_type() -> ContentType {
        ContentType::Json
    }

    fn to_value(&self) -> Result<Value, Error> {
        let ty = Type::json()?;
        let s = serde_json::to_string(self)?;
        Value::of_string(ty, s)
    }

    fn from_value(v: &Value) -> Result<Self, Error> {
        let s = v.to_string()?;
        serde_json::from_str(s.as_ref()).map_err(Error::from)
    }
}

const ROOT_KEY: &str = "root\0";

impl<T: Contents> Config<T> {
    pub fn pack(hash: Option<HashType>) -> Result<Config<T>, Error> {
        unsafe {
            let hash = HashType::ptr(hash);
            let contents = ContentType::ptr(Some(T::content_type()));
            let ptr = irmin_config_pack(hash as *mut _, contents as *mut _);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Config {
                ptr,
                _t: std::marker::PhantomData,
            })
        }
    }

    pub fn mem(hash: Option<HashType>) -> Result<Config<T>, Error> {
        unsafe {
            let hash = HashType::ptr(hash);
            let contents = ContentType::ptr(Some(T::content_type()));
            let ptr = irmin_config_mem(hash as *mut _, contents as *mut _);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Config {
                ptr,
                _t: std::marker::PhantomData,
            })
        }
    }

    pub fn fs(hash: Option<HashType>) -> Result<Config<T>, Error> {
        unsafe {
            let hash = HashType::ptr(hash);
            let contents = ContentType::ptr(Some(T::content_type()));
            let ptr = irmin_config_fs(hash as *mut _, contents as *mut _);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Config {
                ptr,
                _t: std::marker::PhantomData,
            })
        }
    }

    pub fn git() -> Result<Config<T>, Error> {
        unsafe {
            let contents = ContentType::ptr(Some(T::content_type()));
            let ptr = irmin_config_git(contents as *mut _);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Config {
                ptr,
                _t: std::marker::PhantomData,
            })
        }
    }

    pub fn git_mem() -> Result<Config<T>, Error> {
        unsafe {
            let contents = ContentType::ptr(Some(T::content_type()));
            let ptr = irmin_config_git_mem(contents as *mut _);
            if ptr.is_null() {
                return Err(Error::NullPtr);
            }

            Ok(Config {
                ptr,
                _t: std::marker::PhantomData,
            })
        }
    }

    pub fn set_root(&mut self, root: impl AsRef<std::path::Path>) -> Result<bool, Error> {
        let t = Type::string()?;
        let v = Value::string(root.as_ref().to_str().expect("Invalid path"))?;
        let x = unsafe { irmin_config_set(self.ptr, ROOT_KEY.as_ptr() as *mut _, t.ptr, v.ptr) };
        Ok(x)
    }
}
