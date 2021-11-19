module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "repo_new"
      (config @-> returning repo)
      (fun config ->
        let (s, config) : config = Root.get config in
        let (module Store) = Irmin_unix.Resolver.Store.generic_keyed s in
        let repo = Lwt_main.run (Store.Repo.v config) in
        Root.create ((module Store : Irmin.Generic_key.S), repo))

  let () = fn "repo_free" (repo @-> returning void) free
end
