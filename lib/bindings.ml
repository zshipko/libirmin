open Ctypes
open Types

let find_config_key config name =
  Irmin.Private.Conf.Spec.find_key (Irmin.Private.Conf.spec config) name

let type_name x = Fmt.to_to_string Irmin.Type.pp_ty x

let free store = Root.release store

module Stubs (I : Cstubs_inverted.INTERNAL) = struct
  let export ?(lock = false) name t f =
    I.internal ~runtime_lock:lock ("irmin_" ^ name) t f

  let () =
    export "key"
      (schema @-> ptr string_opt @-> returning key)
      (fun schema arr ->
        let rec loop i acc =
          match !@(arr +@ i) with
          | None -> List.rev acc
          | Some x -> loop (i + 1) (x :: acc)
        in
        let l = loop 0 [] in
        let (module Store : Irmin.S), _ = Root.get schema in
        let l =
          List.map
            (fun x -> Irmin.Type.of_string Store.step_t x |> Result.get_ok)
            l
        in
        Store.Key.v l |> Root.create)

  let () =
    export "type_unit"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Type.unit)

  let () =
    export "value_unit" (void @-> returning value) (fun () -> Root.create ())

  let () =
    export "type_bool"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Type.bool)

  let () =
    export "value_bool" (bool @-> returning value) (fun b -> Root.create b)

  let () =
    export "type_int"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Type.int)

  let () = export "value_int" (int @-> returning value) (fun i -> Root.create i)

  let () =
    export "type_string"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Type.string)

  let () =
    export "value_string" (string @-> returning value) (fun s -> Root.create s)

  let () =
    export "value_to_string"
      (ty @-> value @-> returning string)
      (fun ty value ->
        let t = Root.get ty in
        let v = Root.get value in
        let s = Irmin.Type.to_string t v in
        s)

  let () =
    export "value_of_string"
      (ty @-> string @-> returning value)
      (fun ty s ->
        let ty = Root.get ty in
        let x = Irmin.Type.(of_string ty) s |> Result.get_ok in
        Root.create x)

  let () =
    export "value_to_bin"
      (value @-> returning string)
      (fun value ->
        let t, v = Root.get value in
        Irmin.Type.(unstage (to_bin_string t)) v)

  let () =
    export "value_of_bin"
      (ty @-> string @-> returning value)
      (fun ty s ->
        let ty = Root.get ty in
        let x = Irmin.Type.(unstage (of_bin_string ty)) s |> Result.get_ok in
        Root.create x)

  let () = export "type_free" (ty @-> returning void) free

  let () = export "value_free" (value @-> returning void) free

  let () =
    export "info_new"
      (schema @-> string @-> string_opt @-> returning info)
      (fun schema message author ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let module Info = Irmin_unix.Info (Store.Info) in
        Root.create (Info.v ?author "%s" message))

  let () =
    export "info_update"
      (schema @-> string @-> string_opt @-> info @-> returning info)
      (fun schema message author info ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let module Info = Irmin_unix.Info (Store.Info) in
        Root.set info (Info.v ?author "%s" message);
        info)

  let () = export "info_free" (info @-> returning void) free

  let () =
    export "config_new"
      (schema @-> returning config)
      (fun schema ->
        let _, spec, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        (*let spec = Irmin.Private.Conf.spec config in*)
        Root.create (Irmin.Private.Conf.empty spec))

  let () = export "config_free" (config @-> returning void) free

  let () =
    export "config_set"
      (config @-> string @-> ty @-> value @-> returning bool)
      (fun (type a) c key ty value ->
        let config : config = Root.get c in
        let k = find_config_key config key in
        let ok, config =
          match k with
          | None -> (false, config)
          | Some (Irmin.Private.Conf.K k) ->
              let t : a ty = Root.get ty in
              if type_name t <> type_name (Irmin.Private.Conf.ty k) then
                (false, config)
              else
                let value = Root.get value in
                (true, Irmin.Private.Conf.add config k value)
        in
        Root.set c config;
        ok)

  let () =
    export "schema_new"
      (string_opt @-> string_opt @-> string_opt @-> returning schema)
      (fun store hash contents ->
        let hash = Option.map Irmin_unix.Resolver.Hash.find hash in
        let s, config =
          Irmin_unix.Resolver.load_config ?store ?hash ?contents ()
        in
        Root.create s)

  let () = export "schema_free" (schema @-> returning void) free

  let () =
    export "repo_new"
      (schema @-> config @-> returning repo)
      (fun schema config ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let config : config = Root.get config in
        Root.create (Lwt_main.run (Store.Repo.v config)))

  let () = export "repo_free" (repo @-> returning void) free

  let () =
    export "master"
      (schema @-> repo @-> returning store)
      (fun schema repo ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let repo : Store.repo repo = Root.get repo in
        Root.create ((module Store : Irmin.S), Lwt_main.run (Store.master repo)))

  let () =
    export "of_branch"
      (schema @-> repo @-> string @-> returning store)
      (fun schema repo name ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let repo : Store.repo repo = Root.get repo in
        let branch =
          Irmin.Type.of_string Store.Branch.t name |> Result.get_ok
        in
        Root.create
          ((module Store : Irmin.S), Lwt_main.run (Store.of_branch repo branch)))

  let () =
    export "set"
      (store @-> key @-> value @-> info @-> returning bool)
      (fun store key value info ->
        let (module Store : Irmin.S), store = Root.get store in
        let info = Root.get info in
        let key : Store.key key = Root.get key in
        let value : Store.contents value = Root.get value in
        let x = Lwt_main.run (Store.set store key value ~info) in
        match x with Ok () -> true | Error _ -> false)

  let () =
    export "get"
      (store @-> key @-> returning value)
      (fun store key ->
        let (module Store : Irmin.S), store = Root.get store in
        let key : Store.key key = Root.get key in
        let x = Lwt_main.run (Store.find store key) in
        match x with Some x -> Root.create x | None -> null)

  let () =
    export "remove"
      (store @-> key @-> info @-> returning void)
      (fun store key info ->
        let (module Store : Irmin.S), store = Root.get store in
        let module Info = Irmin_unix.Info (Store.Info) in
        let info = Root.get info in
        let key : Store.key key = Root.get key in
        Lwt_main.run (Store.remove store key ~info) |> Result.get_ok)

  let () = export "free" (store @-> returning void) free
end
