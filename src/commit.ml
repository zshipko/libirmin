module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "commit_info"
      (repo @-> commit @-> returning info)
      (fun repo commit ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let commit = Root.get commit in
        Root.create (Store.Commit.info commit))

  let () =
    fn "commit_hash"
      (repo @-> commit @-> returning hash)
      (fun repo commit ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let commit = Root.get commit in
        Root.create (Store.Commit.hash commit))

  let () =
    fn "commit_of_hash"
      (repo @-> hash @-> returning commit)
      (fun repo hash ->
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        let hash = Root.get hash in
        let commit = run (Store.Commit.of_hash repo hash) in
        match commit with Some c -> Root.create c | None -> null)

  let () =
    fn "commit_new"
      (repo @-> ptr commit @-> uint64_t @-> tree @-> info @-> returning commit)
      (fun repo parents n tree info ->
        let n = UInt64.to_int n in
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        let parents =
          if is_null parents || n = 0 then []
          else
            CArray.from_ptr parents n |> CArray.to_list |> List.map Root.get
            |> List.map Store.Commit.key
        in
        let tree = Root.get tree in
        let info = Root.get info in
        let commit = run (Store.Commit.v repo ~parents ~info tree) in
        Root.create commit)

  let () =
    fn "commit_parents_length"
      (repo @-> commit @-> returning uint64_t)
      (fun repo commit ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let commit = Root.get commit in
        let parents = Store.Commit.parents commit in
        List.length parents |> UInt64.of_int)

  let () =
    fn "commit_parent"
      (repo @-> commit @-> uint64_t @-> returning commit)
      (fun repo commit i ->
        let i = UInt64.to_int i in
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        let commit = Root.get commit in
        let parents = Store.Commit.parents commit in
        try
          run (List.nth parents i |> Store.Commit.of_key repo)
          |> Option.get |> Root.create
        with _ -> null)

  let () =
    fn "commit_equal"
      (repo @-> commit @-> commit @-> returning bool)
      (fun repo a b ->
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        let a = Root.get a in
        let b = Root.get b in
        Irmin.Type.(unstage (equal (Store.commit_t repo))) a b)

  let () = fn "commit_free" (commit @-> returning void) free
end
