module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "commit_info"
      (schema @-> commit @-> returning info)
      (fun schema commit ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let commit = Root.get commit in
        Root.create (Store.Commit.info commit))

  let () =
    fn "commit_hash"
      (schema @-> commit @-> returning hash)
      (fun schema commit ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let commit = Root.get commit in
        Root.create (Store.Commit.hash commit))

  let () =
    fn "commit_of_hash"
      (schema @-> repo @-> hash @-> returning commit)
      (fun schema repo hash ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let repo = Root.get repo in
        let hash = Root.get hash in
        let commit = Lwt_main.run (Store.Commit.of_hash repo hash) in
        match commit with Some c -> Root.create c | None -> null)

  let () =
    fn "commit_parents_length"
      (schema @-> commit @-> returning int)
      (fun schema commit ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let commit = Root.get commit in
        let parents = Store.Commit.parents commit in
        List.length parents)

  let () =
    fn "commit_parent"
      (schema @-> commit @-> int @-> returning commit)
      (fun schema commit i ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let commit = Root.get commit in
        let parents = Store.Commit.parents commit in
        try List.nth parents i |> Root.create with _ -> null)

  let () = fn "commit_free" (commit @-> returning void) free
end
