use irmin::*;

fn list_path<T: Contents>(store: &Store<T>, path: Path) -> Result<(), Error> {
    for k in store.list(&path)? {
        let p = path.append_path(&k)?;

        // If the store has contents at `p` then print the path
        if store.mem(&p) {
            println!("{}", path.to_string()?);
        } else {
            list_path(store, p)?;
        }
    }

    Ok(())
}

fn main() -> Result<(), Error> {
    let args: Vec<_> = std::env::args().collect();

    if args.len() < 2 {
        println!("usage {} /path/to/tezos/context", &args[0]);
        return Ok(());
    }

    // Configure an in-memory store with `Json` contents
    let mut config = Config::<IrminString>::tezos()?;
    config.set_root(&args[1])?;

    // Initialize the repo
    let repo = Repo::new(config)?;

    // Open the main branch
    let store = Store::of_branch(&repo, "master")?;

    // List content paths
    let path = Path::new(&repo, &["data", "contracts"])?;
    list_path(&store, path)?;

    Ok(())
}
