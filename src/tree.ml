module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "tree_new"
      (repo @-> returning tree)
      (fun (type repo) repo ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        Root.create_tree (module Store) (Store.Tree.empty ()))

  let () =
    fn "tree_clone"
      (repo @-> tree @-> returning tree)
      (fun (type repo) repo tree ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let tree : Store.tree = Root.get_tree (module Store) tree in
        Root.create_tree (module Store) tree)

  let () =
    fn "tree_mem"
      (repo @-> tree @-> path @-> returning bool)
      (fun (type repo) repo tree path ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let tree : Store.tree = Root.get_tree (module Store) tree in
        let path : Store.path = Root.get_path (module Store) path in
        run (Store.Tree.mem tree path))

  let () =
    fn "tree_mem_tree"
      (repo @-> tree @-> path @-> returning bool)
      (fun (type repo) repo tree path ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let tree : Store.tree = Root.get_tree (module Store) tree in
        let path : Store.path = Root.get_path (module Store) path in
        run (Store.Tree.mem_tree tree path))

  let () =
    fn "tree_find"
      (repo @-> tree @-> path @-> returning value)
      (fun (type repo) repo tree path ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let tree : Store.tree = Root.get_tree (module Store) tree in
        let path : Store.path = Root.get_path (module Store) path in
        match run (Store.Tree.find tree path) with
        | None -> null
        | Some x -> Root.create_contents (module Store) x)

  let () =
    fn "tree_find_tree"
      (repo @-> tree @-> path @-> returning tree)
      (fun (type repo) repo tree path ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let tree : Store.tree = Root.get_tree (module Store) tree in
        let path : Store.path = Root.get_path (module Store) path in
        match run (Store.Tree.find_tree tree path) with
        | None -> null
        | Some x -> Root.create_tree (module Store) x)

  let () =
    fn "tree_add"
      (repo @-> tree @-> path @-> value @-> returning void)
      (fun (type repo) repo tree path value ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let tree' : Store.tree = Root.get_tree (module Store) tree in
        let path : Store.path = Root.get_path (module Store) path in
        let value : Store.contents = Root.get_contents (module Store) value in
        let t = run (Store.Tree.add tree' path value) in
        Root.set_tree (module Store) tree t)

  let () =
    fn "tree_add_tree"
      (repo @-> tree @-> path @-> tree @-> returning void)
      (fun (type repo) repo tree path tr ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let tree' : Store.tree = Root.get_tree (module Store) tree in
        let path : Store.path = Root.get_path (module Store) path in
        let value : Store.tree = Root.get_tree (module Store) tr in
        let t = run (Store.Tree.add_tree tree' path value) in
        Root.set_tree (module Store) tree t)

  let () =
    fn "tree_remove"
      (repo @-> tree @-> path @-> returning void)
      (fun (type repo) repo tree path ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let tree' : Store.tree = Root.get_tree (module Store) tree in
        let path : Store.path = Root.get_path (module Store) path in
        let t = run (Store.Tree.remove tree' path) in
        Root.set_tree (module Store) tree t)

  let () =
    fn "tree_equal"
      (repo @-> tree @-> tree @-> returning bool)
      (fun (type repo) repo a b ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let a = Root.get_tree (module Store) a in
        let b = Root.get_tree (module Store) b in
        Irmin.Type.(unstage (equal Store.tree_t)) a b)

  let () = fn "tree_free" (tree @-> returning void) free
end
