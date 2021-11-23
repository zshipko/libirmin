mod commit;
mod config;
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
}

pub use crate::prelude::*;

#[derive(Debug)]
pub enum Error {
    NullPtr,
}

#[cfg(test)]
mod tests {
    use crate::*;
    #[test]
    fn it_works() -> Result<(), Error> {
        println!("A");
        let config = Config::<String>::git_mem()?;

        println!("B");
        let repo = Repo::new(config)?;

        println!("C");
        let store = Store::new(&repo)?;

        let info = Info::new(&repo, "irmin", "set")?;
        let path = Path::new(&repo, "a/b/c")?;
        assert!(store.set(&path, &String::from("testing"), info)?);

        let s = store.find(&path)?;
        assert!(s == Some("testing".to_string()));
        Ok(())
    }
}
