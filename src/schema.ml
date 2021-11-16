module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "schema_pack"
      (string_opt @-> string_opt @-> returning schema)
      (fun hash contents ->
        let hash = Option.map Irmin_unix.Resolver.Hash.find hash in
        let s, config =
          Irmin_unix.Resolver.load_config ~store:"pack" ?hash ?contents ()
        in
        Root.create s)

  let () =
    fn "schema_git"
      (string_opt @-> returning schema)
      (fun contents ->
        let s, config =
          Irmin_unix.Resolver.load_config ~store:"git" ?contents ()
        in
        Root.create s)

  let () =
    fn "schema_fs"
      (string_opt @-> string_opt @-> returning schema)
      (fun hash contents ->
        let hash = Option.map Irmin_unix.Resolver.Hash.find hash in
        let s, config =
          Irmin_unix.Resolver.load_config ~store:"irf" ?hash ?contents ()
        in
        Root.create s)

  let () =
    fn "schema_mem"
      (string_opt @-> string_opt @-> returning schema)
      (fun hash contents ->
        let hash = Option.map Irmin_unix.Resolver.Hash.find hash in
        let s, config =
          Irmin_unix.Resolver.load_config ~store:"mem" ?hash ?contents ()
        in
        Root.create s)

  let () = fn "schema_free" (schema @-> returning void) free
end
