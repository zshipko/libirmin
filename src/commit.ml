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
    fn "commit_parents"
      (schema @-> commit @-> ptr int @-> returning (ptr commit))
      (fun schema commit out ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let commit = Root.get commit in
        let parents = Store.Commit.parents commit |> List.map Root.create in
        let () = if not (is_null out) then out <-@ List.length parents in
        CArray.of_list commit (parents @ [ null ]) |> CArray.start)

  let () = fn "commit_free" (commit @-> returning void) free

  let () =
    fn "commit_parents_free"
      (ptr commit @-> returning void)
      (fun commits ->
        let len = ref 0 in
        let r = ref commits in
        let () =
          while not (is_null !r) do
            r := !r +@ 1;
            incr len
          done
        in
        let arr = CArray.from_ptr commits !len in
        CArray.iter free arr)
end
