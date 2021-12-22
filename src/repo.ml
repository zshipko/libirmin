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
      (repo @-> branch_list @-> returning uint64_t)
      (fun (type repo) repo p ->
        catch UInt64.zero (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let arr = Root.get_branch_list (module Store) p in
            UInt64.of_int (Array.length arr)))

  let () =
    fn "branch_list_get"
      (repo @-> branch_list @-> uint64_t @-> returning irmin_string)
      (fun (type repo) repo p i ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let i = UInt64.to_int i in
        let arr = Root.get_branch_list (module Store) p in
        if i >= Array.length arr then null
        else
          let x = Array.unsafe_get arr i in
          Root.create_string (Irmin.Type.to_string Store.Branch.t x))

  let () = fn "branch_list_free" (branch_list @-> returning void) free
  let () = fn "repo_free" (repo @-> returning void) free
end
