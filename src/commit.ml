module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "commit_info"
      (repo @-> commit @-> returning info)
      (fun (type repo) repo commit ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let commit = Root.get_commit (module Store) commit in
        Root.create_info (module Store) (Store.Commit.info commit))

  let () =
    fn "commit_hash"
      (repo @-> commit @-> returning hash)
      (fun (type repo) repo commit ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let commit = Root.get_commit (module Store) commit in
        Root.create_hash (module Store) (Store.Commit.hash commit))

  let () =
    fn "commit_of_hash"
      (repo @-> hash @-> returning commit)
      (fun (type repo) repo hash ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), repo =
          Root.get_repo repo
        in
        let hash = Root.get_hash (module Store) hash in
        let commit = run (Store.Commit.of_hash repo hash) in
        match commit with
        | Some c -> Root.create_commit (module Store) c
        | None -> null)

  let () =
    fn "commit_new"
      (repo @-> ptr commit @-> uint64_t @-> tree @-> info @-> returning commit)
      (fun (type repo) repo parents n tree info ->
        let n = UInt64.to_int n in
        let (module Store : Irmin.Generic_key.S with type repo = repo), repo =
          Root.get_repo repo
        in
        let parents =
          if is_null parents || n = 0 then []
          else
            CArray.from_ptr parents n |> CArray.to_list
            |> List.map (Root.get_commit (module Store))
            |> List.map Store.Commit.key
        in
        let tree = Root.get_tree (module Store) tree in
        let info = Root.get_info (module Store) info in
        let commit = run (Store.Commit.v repo ~parents ~info tree) in
        Root.create_commit (module Store) commit)

  let () =
    fn "commit_parents"
      (repo @-> commit @-> returning irmin_list)
      (fun (type repo) repo commit ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), repo =
          Root.get_repo repo
        in
        let commit = Root.get_commit (module Store) commit in
        let parents = Store.Commit.parents commit in
        let open Lwt.Infix in
        try
          Lwt_list.map_s
            (fun x ->
              Store.Commit.of_key repo x >|= fun c ->
              Option.get c |> Root.create_commit (module Store))
            parents
          |> run |> Root.create_list
        with _ -> null)

  let () =
    fn "commit_parents_length"
      (repo @-> commit @-> returning uint64_t)
      (fun (type repo) repo commit ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let commit = Root.get_commit (module Store) commit in
        let parents = Store.Commit.parents commit in
        List.length parents |> UInt64.of_int)

  let () =
    fn "commit_parent"
      (repo @-> commit @-> uint64_t @-> returning commit)
      (fun (type repo) repo commit i ->
        let i = UInt64.to_int i in
        let (module Store : Irmin.Generic_key.S with type repo = repo), repo =
          Root.get_repo repo
        in
        let commit = Root.get_commit (module Store) commit in
        let parents = Store.Commit.parents commit in
        try
          run (List.nth parents i |> Store.Commit.of_key repo)
          |> Option.get
          |> Root.create_commit (module Store)
        with _ -> null)

  let () =
    fn "commit_equal"
      (repo @-> commit @-> commit @-> returning bool)
      (fun (type repo) repo a b ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), repo =
          Root.get_repo repo
        in
        let a = Root.get_commit (module Store) a in
        let b = Root.get_commit (module Store) b in
        Irmin.Type.(unstage (equal (Store.commit_t repo))) a b)

  let () = fn "commit_free" (commit @-> returning void) free
end
