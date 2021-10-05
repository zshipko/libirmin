module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "info_new"
      (schema @-> string @-> string_opt @-> returning info)
      (fun schema message author ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let module Info = Irmin_unix.Info (Store.Info) in
        Root.create (Info.v ?author "%s" message))

  let () =
    fn "info_update"
      (schema @-> string @-> string_opt @-> info @-> returning info)
      (fun schema message author info ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let module Info = Irmin_unix.Info (Store.Info) in
        Root.set info (Info.v ?author "%s" message);
        info)

  let () = fn "info_free" (info @-> returning void) free
end
