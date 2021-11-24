mod commit;
mod config;
mod hash;
mod info;
mod irmin_string;
mod path;
mod repo;
mod store;
mod tree;
mod ty;
mod value;

pub mod bindings;

pub(crate) mod prelude {
    pub use crate::commit::Commit;
    pub use crate::config::{Config, ContentType, Contents, HashType};
    pub use crate::hash::Hash;
    pub use crate::info::Info;
    pub use crate::irmin_string::IrminString;
    pub use crate::path::Path;
    pub use crate::repo::Repo;
    pub use crate::store::Store;
    pub use crate::tree::Tree;
    pub use crate::ty::Type;
    pub use crate::value::Value;
    pub use crate::Error;
}

pub(crate) mod internal {
    pub use crate::bindings::*;
    pub use crate::prelude::*;

    pub(crate) fn cstring(s: impl AsRef<str>) -> String {
        let mut s = s.as_ref().to_string();
        s.push('\0');
        s
    }
}

pub use crate::prelude::*;

#[derive(Debug)]
pub enum Error {
    NullPtr,
    Json(serde_json::Error),
}

impl From<serde_json::Error> for Error {
    fn from(e: serde_json::Error) -> Error {
        Error::Json(e)
    }
}

#[cfg(test)]
mod tests {
    use crate::*;
    #[test]
    fn it_works() -> Result<(), Error> {
        println!("A");
        let config = Config::<serde_json::Value>::git_mem()?;

        println!("B");
        let repo = Repo::new(config)?;

        println!("C");
        let mut store = Store::new(&repo)?;

        let info = Info::new(&repo, "irmin", "set")?;
        let path = Path::new(&repo, "foo/bar")?;
        let value = serde_json::json!({
            "a": 1,
            "b": 2,
            "c": 3,
        });
        assert!(store.set(&path, &value, info)?);

        let s = store.find(&path)?;
        assert!(s == Some(value));

        let path1 = path.parent().unwrap();
        assert!(store.mem_tree(&path1));
        Ok(())
    }
}
