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

  let () = fn "repo_free" (repo @-> returning void) free
end
