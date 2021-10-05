module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "schema_new"
      (string_opt @-> string_opt @-> string_opt @-> returning schema)
      (fun store hash contents ->
        let hash = Option.map Irmin_unix.Resolver.Hash.find hash in
        let s, config =
          Irmin_unix.Resolver.load_config ?store ?hash ?contents ()
        in
        Root.create s)

  let () = fn "schema_free" (schema @-> returning void) free
end
