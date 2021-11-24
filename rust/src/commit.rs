use crate::internal::*;

pub struct Commit<'a> {
    pub ptr: *mut IrminCommit,
    pub(crate) repo_ptr: *mut IrminRepo,
    pub(crate) _t: std::marker::PhantomData<&'a ()>,
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
            repo_ptr: repo.ptr,
            _t: std::marker::PhantomData,
        })
    }

    pub fn hash(&self) -> Result<Hash, Error> {
        let ptr = unsafe { irmin_commit_hash(self.repo_ptr, self.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Hash {
            ptr,
            repo_ptr: self.repo_ptr,
            _t: std::marker::PhantomData,
        })
    }

    pub fn info(&self) -> Result<Info, Error> {
        let ptr = unsafe { irmin_commit_info(self.repo_ptr, self.ptr) };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Info {
            ptr,
            repo_ptr: self.repo_ptr,
            _t: std::marker::PhantomData,
        })
    }
}
