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
      (repo @-> commit @-> tree @-> info @-> returning commit)
      (fun repo parent tree info ->
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        let parent = Root.get parent in
        let parent = Store.Commit.key parent in
        let tree = Root.get tree in
        let info = Root.get info in
        let commit = run (Store.Commit.v repo ~parents:[ parent ] ~info tree) in
        Root.create commit)

  let () =
    fn "commit_parents_length"
      (repo @-> commit @-> returning int)
      (fun repo commit ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let commit = Root.get commit in
        let parents = Store.Commit.parents commit in
        List.length parents)

  let () =
    fn "commit_parent"
      (repo @-> commit @-> int @-> returning commit)
      (fun repo commit i ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let commit = Root.get commit in
        let parents = Store.Commit.parents commit in
        try List.nth parents i |> Root.create with _ -> null)

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
