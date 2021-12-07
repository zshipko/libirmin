module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "info_new"
      (repo @-> string_opt @-> string @-> returning info)
      (fun repo author message ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let module Info = Irmin_unix.Info (Store.Info) in
        let info : Info.t = Info.v ?author "%s" message () in
        Root.create info)

  let () =
    fn "info_update"
      (repo @-> string @-> string_opt @-> info @-> returning info)
      (fun repo message author info ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let module Info = Irmin_unix.Info (Store.Info) in
        Root.set info (Info.v ?author "%s" message);
        info)

  let () =
    fn "info_message"
      (repo @-> info @-> ptr uint64_t @-> returning (ptr char))
      (fun repo info l ->
        let info = Root.get info in
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let s = Store.Info.message info in
        if not (is_null l) then l <-@ UInt64.of_int @@ String.length s;
        malloc_string s)

  let () =
    fn "info_author"
      (repo @-> info @-> ptr uint64_t @-> returning (ptr char))
      (fun repo info l ->
        let info = Root.get info in
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let s = Store.Info.author info in
        if not (is_null l) then l <-@ UInt64.of_int @@ String.length s;
        malloc_string s)

  let () =
    fn "info_date"
      (repo @-> info @-> returning int64_t)
      (fun repo info ->
        let info = Root.get info in
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        Store.Info.date info)

  let () = fn "info_free" (info @-> returning void) free
end
