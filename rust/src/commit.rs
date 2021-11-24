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

impl<'a> PartialEq for Commit<'a> {
    fn eq(&self, other: &Commit<'a>) -> bool {
        unsafe { irmin_commit_equal(self.repo.ptr, self.ptr, other.ptr) }
    }
}

impl<'a> Commit<'a> {
    pub fn new<T: Contents>(
        repo: &'a Repo<T>,
        parents: impl AsRef<[&'a Commit<'a>]>,
        tree: &Tree<T>,
        info: Info,
    ) -> Result<Commit<'a>, Error> {
        let parents: Vec<_> = parents.as_ref().into_iter().map(|x| x.ptr).collect();
        let ptr = unsafe {
            irmin_commit_new(
                repo.ptr,
                parents.as_ptr() as *mut _,
                parents.len() as i32,
                tree.ptr,
                info.ptr,
            )
        };
        if ptr.is_null() {
            return Err(Error::NullPtr);
        }
        Ok(Commit {
            ptr,
            repo: UntypedRepo::new(repo),
        })
    }

    pub fn of_hash<T: Contents>(repo: &'a Repo<T>, hash: &Hash) -> Result<Commit<'a>, Error> {
        let ptr = unsafe { irmin_commit_of_hash(repo.ptr, hash.ptr) };
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

    pub fn parents(&self) -> Vec<Commit> {
        let mut dest = Vec::new();
        let len = unsafe { irmin_commit_parents_length(self.repo.ptr, self.ptr) };
        for i in 0..len {
            let ptr = unsafe { irmin_commit_parent(self.repo.ptr, self.ptr, i) };
            if ptr.is_null() {
                continue;
            }
            dest.push(Commit {
                ptr,
                repo: self.repo.clone(),
            });
        }
        dest
    }
}
