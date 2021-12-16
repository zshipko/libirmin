module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "repo_new"
      (config @-> returning repo)
      (fun config ->
        catch' (fun () ->
            let (s, config) : config = Root.get_config config in
            let (module Store) = Irmin_unix.Resolver.Store.generic_keyed s in
            let repo : Store.repo = run (Store.Repo.v config) in
            Root.create_repo
              (module Store)
              ( (module Store : Irmin.Generic_key.S with type repo = Store.repo),
                repo )))

  let () =
    fn "repo_branches"
      (repo @-> returning branch_list)
      (fun (type repo) repo ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), repo
                =
              Root.get_repo repo
            in
            let b = run (Store.Repo.branches repo) in
            Root.create_branch_list (module Store) b))

  let () =
    fn "branch_list_length"
      (branch_list @-> returning uint64_t)
      (fun p ->
        catch UInt64.zero (fun () ->
            let arr = Root.get_branch_list p in
            UInt64.of_int (CArray.length arr)))

  let () =
    fn "branch_list_get"
      (branch_list @-> uint64_t @-> returning irmin_string)
      (fun p i ->
        let i = UInt64.to_int i in
        let arr = Root.get_branch_list p in
        if i >= CArray.length arr then null
        else
          let x = CArray.unsafe_get arr i in
          let s : string = Ctypes.Root.get x in
          Ctypes.Root.create s)

  let () =
    fn "branch_list_free"
      (branch_list @-> returning void)
      (fun p ->
        let arr = Root.get_branch_list p in
        CArray.iter (fun x -> free x) arr;
        free p)

  let () = fn "repo_free" (repo @-> returning void) free
end
