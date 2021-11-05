module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "tree_new"
      (schema @-> returning tree)
      (fun schema ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        Root.create Store.Tree.empty)

  let () =
    fn "tree_clone"
      (schema @-> tree @-> returning tree)
      (fun schema tree ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        Root.create tree)

  let () =
    fn "tree_mem"
      (schema @-> tree @-> path @-> returning bool)
      (fun schema tree path ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        Lwt_main.run (Store.Tree.mem tree path))

  let () =
    fn "tree_mem_tree"
      (schema @-> tree @-> path @-> returning bool)
      (fun schema tree path ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        Lwt_main.run (Store.Tree.mem_tree tree path))

  let () =
    fn "tree_find"
      (schema @-> tree @-> path @-> returning value)
      (fun schema tree path ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        match Lwt_main.run (Store.Tree.find tree path) with
        | None -> null
        | Some x -> Root.create x)

  let () =
    fn "tree_find_tree"
      (schema @-> tree @-> path @-> returning tree)
      (fun schema tree path ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        match Lwt_main.run (Store.Tree.find_tree tree path) with
        | None -> null
        | Some x -> Root.create x)

  let () =
    fn "tree_add"
      (schema @-> tree @-> path @-> value @-> returning void)
      (fun schema tree path value ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree' : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        let value : Store.contents = Root.get value in
        let t = Lwt_main.run (Store.Tree.add tree' path value) in
        Root.set tree t)

  let () =
    fn "tree_add_tree"
      (schema @-> tree @-> path @-> tree @-> returning void)
      (fun schema tree path tr ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree' : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        let value : Store.tree = Root.get tr in
        let t = Lwt_main.run (Store.Tree.add_tree tree' path value) in
        Root.set tree t)

  let () =
    fn "tree_remove"
      (schema @-> tree @-> path @-> returning void)
      (fun schema tree path ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree' : Store.tree = Root.get tree in
        let path : Store.path = Root.get path in
        let t = Lwt_main.run (Store.Tree.remove tree' path) in
        Root.set tree t)

  let () = fn "tree_free" (tree @-> returning void) free
end
