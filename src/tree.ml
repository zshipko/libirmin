module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "tree_new"
      (repo @-> returning tree)
      (fun repo ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        Root.create (Store.Tree.empty ()))

  let () =
    fn "tree_clone"
      (repo @-> tree @-> returning tree)
      (fun repo tree ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let tree : Store.tree = Root.get tree in
        Root.create tree)

  let () =
    fn "tree_mem"
      (repo @-> tree @-> path @-> returning bool)
      (fun repo tree path ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let tree : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        Lwt_main.run (Store.Tree.mem tree path))

  let () =
    fn "tree_mem_tree"
      (repo @-> tree @-> path @-> returning bool)
      (fun repo tree path ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let tree : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        Lwt_main.run (Store.Tree.mem_tree tree path))

  let () =
    fn "tree_find"
      (repo @-> tree @-> path @-> returning value)
      (fun repo tree path ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let tree : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        match Lwt_main.run (Store.Tree.find tree path) with
        | None -> null
        | Some x -> Root.create x)

  let () =
    fn "tree_find_tree"
      (repo @-> tree @-> path @-> returning tree)
      (fun repo tree path ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let tree : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        match Lwt_main.run (Store.Tree.find_tree tree path) with
        | None -> null
        | Some x -> Root.create x)

  let () =
    fn "tree_add"
      (repo @-> tree @-> path @-> value @-> returning void)
      (fun repo tree path value ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let tree' : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        let value : Store.contents = Root.get value in
        let t = Lwt_main.run (Store.Tree.add tree' path value) in
        Root.set tree t)

  let () =
    fn "tree_add_tree"
      (repo @-> tree @-> path @-> tree @-> returning void)
      (fun repo tree path tr ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let tree' : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        let value : Store.tree = Root.get tr in
        let t = Lwt_main.run (Store.Tree.add_tree tree' path value) in
        Root.set tree t)

  let () =
    fn "tree_remove"
      (repo @-> tree @-> path @-> returning void)
      (fun repo tree path ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let tree' : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        let t = Lwt_main.run (Store.Tree.remove tree' path) in
        Root.set tree t)

  let () =
    fn "tree_equal"
      (repo @-> tree @-> tree @-> returning bool)
      (fun repo a b ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let a = Root.get a in
        let b = Root.get b in
        Irmin.Type.(unstage (equal Store.tree_t)) a b)

  let () = fn "tree_free" (tree @-> returning void) free
end
