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
      (schema @-> tree @-> key @-> returning bool)
      (fun schema tree key ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        let key : Store.key = Root.get key in
        Lwt_main.run (Store.Tree.mem tree key))

  let () =
    fn "tree_mem_tree"
      (schema @-> tree @-> key @-> returning bool)
      (fun schema tree key ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        let key : Store.key = Root.get key in
        Lwt_main.run (Store.Tree.mem_tree tree key))

  let () =
    fn "tree_find"
      (schema @-> tree @-> key @-> returning value)
      (fun schema tree key ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        let key : Store.key = Root.get key in
        match Lwt_main.run (Store.Tree.find tree key) with
        | None -> null
        | Some x -> Root.create x)

  let () =
    fn "tree_find_tree"
      (schema @-> tree @-> key @-> returning tree)
      (fun schema tree key ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree : Store.tree = Root.get tree in
        let key : Store.key = Root.get key in
        match Lwt_main.run (Store.Tree.find_tree tree key) with
        | None -> null
        | Some x -> Root.create x)

  let () =
    fn "tree_add"
      (schema @-> tree @-> key @-> value @-> returning void)
      (fun schema tree key value ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree' : Store.tree = Root.get tree in
        let key : Store.key = Root.get key in
        let value : Store.contents = Root.get value in
        let t = Lwt_main.run (Store.Tree.add tree' key value) in
        Root.set tree t)

  let () =
    fn "tree_add_tree"
      (schema @-> tree @-> key @-> tree @-> returning void)
      (fun schema tree key tr ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree' : Store.tree = Root.get tree in
        let key : Store.key = Root.get key in
        let value : Store.tree = Root.get tr in
        let t = Lwt_main.run (Store.Tree.add_tree tree' key value) in
        Root.set tree t)

  let () =
    fn "tree_remove"
      (schema @-> tree @-> key @-> returning void)
      (fun schema tree key ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let tree' : Store.tree = Root.get tree in
        let key : Store.key = Root.get key in
        let t = Lwt_main.run (Store.Tree.remove tree' key) in
        Root.set tree t)

  let () = fn "tree_free" (tree @-> returning void) free
end
