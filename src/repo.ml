module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "repo_new"
      (schema @-> config @-> returning repo)
      (fun schema config ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let config : config = Root.get config in
        Root.create (Lwt_main.run (Store.Repo.v config)))

  let () = fn "repo_free" (repo @-> returning void) free
end
