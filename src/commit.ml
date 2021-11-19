open Lwt.Infix

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
        let commit =
          Lwt_main.run (repo >>= fun r -> Store.Commit.of_hash r hash)
        in
        match commit with Some c -> Root.create c | None -> null)

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

  let () = fn "commit_free" (commit @-> returning void) free
end
