module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let make_schema name =
    fn ("schema_" ^ name)
      (string_opt @-> string_opt @-> returning schema)
      (fun hash contents ->
        let hash = Option.map Irmin_unix.Resolver.Hash.find hash in
        let s, config =
          Irmin_unix.Resolver.load_config ~store:name ?hash ?contents ()
        in
        Root.create s)

  let () = make_schema "pack"

  let () = make_schema "git"

  let () = make_schema "irf"

  let () = make_schema "mem"

  let () = fn "schema_free" (schema @-> returning void) free
end
