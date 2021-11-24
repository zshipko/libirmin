use crate::internal::*;

pub struct Commit<'a> {
    pub ptr: *mut IrminCommit,
    pub(crate) repo: UntypedRepo<'a>,
}

impl<'a> Drop for Commit<'a> {
    fn drop(&mut self) {
        unsafe { irmin_commit_free(self.ptr) }
    }
}

impl<'a> Commit<'a> {
    pub fn new<T: Contents>(
        repo: &'a Repo<T>,
        parent: &Commit,
        tree: &Tree<T>,
        info: Info,
    ) -> Result<Commit<'a>, Error> {
        let ptr = unsafe { irmin_commit_new(repo.ptr, parent.ptr, tree.ptr, info.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Commit {
            ptr,
            repo: UntypedRepo::new(repo),
        })
    }

    pub fn hash(&self) -> Result<Hash, Error> {
        let ptr = unsafe { irmin_commit_hash(self.repo.ptr, self.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Hash {
            ptr,
            repo: self.repo.clone(),
        })
    }

    pub fn info(&self) -> Result<Info, Error> {
        let ptr = unsafe { irmin_commit_info(self.repo.ptr, self.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Info {
            ptr,
            repo: self.repo.clone(),
        })
    }
}
