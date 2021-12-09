module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "info_new"
      (repo @-> string_opt @-> string @-> returning info)
      (fun (type repo) repo author message ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let module Info = Irmin_unix.Info (Store.Info) in
        let info : Info.t = Info.v ?author "%s" message () in
        Root.create_info (module Store) info)

  let () =
    fn "info_update"
      (repo @-> info @-> string_opt @-> string @-> returning void)
      (fun (type repo) repo info author message ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let module Info = Irmin_unix.Info (Store.Info) in
        Root.set_info (module Store) info (Info.v ?author "%s" message ()))

  let () =
    fn "info_message"
      (repo @-> info @-> ptr uint64_t @-> returning (ptr char))
      (fun (type repo) repo info l ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let info = Root.get_info (module Store) info in
        let s = Store.Info.message info in
        if not (is_null l) then l <-@ UInt64.of_int @@ String.length s;
        malloc_string s)

  let () =
    fn "info_author"
      (repo @-> info @-> ptr uint64_t @-> returning (ptr char))
      (fun (type repo) repo info l ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let info = Root.get_info (module Store) info in
        let s = Store.Info.author info in
        if not (is_null l) then l <-@ UInt64.of_int @@ String.length s;
        malloc_string s)

  let () =
    fn "info_date"
      (repo @-> info @-> returning int64_t)
      (fun (type repo) repo info ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let info = Root.get_info (module Store) info in
        Store.Info.date info)

  let () = fn "info_free" (info @-> returning void) free
end
