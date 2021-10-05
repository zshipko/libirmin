module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "config_new"
      (schema @-> returning config)
      (fun schema ->
        let _, spec, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        (*let spec = Irmin.Backend.Conf.spec config in*)
        Root.create (Irmin.Backend.Conf.empty spec))

  let () = fn "config_free" (config @-> returning void) free

  let () =
    fn "config_set"
      (config @-> string @-> ty @-> value @-> returning bool)
      (fun (type a) c key ty value ->
        let config : config = Root.get c in
        let k = find_config_key config key in
        let ok, config =
          match k with
          | None -> (false, config)
          | Some (Irmin.Backend.Conf.K k) ->
              let t : a Irmin.Type.t = Root.get ty in
              if type_name t <> type_name (Irmin.Backend.Conf.ty k) then
                (false, config)
              else
                let value = Root.get value in
                (true, Irmin.Backend.Conf.add config k value)
        in
        Root.set c config;
        ok)
end
