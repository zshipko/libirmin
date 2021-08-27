open Ctypes

let spec = Irmin.Private.Conf.Spec.v "test"

let config = ptr (typedef void "IrminConfig")

let repo = ptr (typedef void "IrminRepo")

let store = ptr (typedef void "Irmin")

let ty = ptr (typedef void "IrminType")

let value = ptr (typedef void "IrminValue")

let schema = ptr (typedef void "IrminSchema")

let key = ptr (typedef void "IrminKey")

let tree = ptr (typedef void "IrminTree")

let commit = ptr (typedef void "IrminCommit")

let info = ptr (typedef void "IrminInfo")

type schema = (module Irmin.S) * Irmin.config

let type_unit () = Root.create Irmin.Type.unit

type 'a value = 'a Irmin.Type.t * 'a

let value_unit () = Root.create (Irmin.Type.unit, ())

let type_bool () = Root.create Irmin.Type.bool

let value_bool b = Root.create (Irmin.Type.bool, b)

let type_int () = Root.create Irmin.Type.int

let value_int i = Root.create (Irmin.Type.int, i)

let type_string () = Root.create Irmin.Type.string

let value_string s = Root.create (Irmin.Type.string, s)

let config_new schema =
  let _, config = Root.get schema in
  let spec = Irmin.Private.Conf.spec config in
  Root.create (Irmin.Private.Conf.empty spec)

let find_config_key name =
  let specs = Irmin.Private.Conf.Spec.list () in
  Seq.fold_left
    (fun acc spec ->
      match acc with
      | Some _ as x -> x
      | None -> Irmin.Private.Conf.Spec.find_key spec name)
    None specs

let type_name x = Fmt.to_to_string Irmin.Type.pp_ty x

let config_set c key value =
  let config : Irmin.config = Root.get c in
  let k = find_config_key key in
  let t, value = Root.get value in
  let ok, config =
    match k with
    | None -> (false, config)
    | Some (Irmin.Private.Conf.K k) ->
        if type_name t <> type_name (Irmin.Private.Conf.ty k) then
          (false, config)
        else (true, Irmin.Private.Conf.add config k value)
  in
  Root.set c config;
  ok

let schema_new store hash contents config_path =
  let hash = Option.map Irmin_unix.Resolver.Hash.find hash in
  let s, config =
    Irmin_unix.Resolver.load_config ?store ?hash ?contents ?config_path ()
  in
  let m, _, _ = Irmin_unix.Resolver.Store.destruct s in
  Root.create (m, config)

let repo_new ctx config =
  let (module Store : Irmin.S), _ = Root.get ctx in
  let config = Root.get config in
  Root.create (Lwt_main.run (Store.Repo.v config))

let master ctx repo =
  let (module Store : Irmin.S), _ = Root.get ctx in
  let repo = Root.get repo in
  Root.create ((module Store : Irmin.S), Lwt_main.run (Store.master repo))

let of_branch ctx repo name =
  let (module Store : Irmin.S), _ = Root.get ctx in
  let repo = Root.get repo in
  let branch = Irmin.Type.of_string Store.Branch.t name |> Result.get_ok in
  Root.create
    ((module Store : Irmin.S), Lwt_main.run (Store.of_branch repo branch))

let free store = Root.release store

let set store key value =
  let (module Store : Irmin.S), store = Root.get store in
  let module Info = Irmin_unix.Info (Store.Info) in
  let key = Root.get key in
  let value = Root.get value in
  let x = Lwt_main.run (Store.set store key value ~info:(Info.v "set")) in
  match x with Ok () -> true | Error _ -> false

let get store key =
  let (module Store : Irmin.S), store = Root.get store in
  let key = Root.get key in
  let x = Lwt_main.run (Store.find store key) in
  match x with Some x -> Root.create x | None -> null

let remove store key =
  let (module Store : Irmin.S), store = Root.get store in
  let module Info = Irmin_unix.Info (Store.Info) in
  let key = Root.get key in
  Lwt_main.run (Store.remove store key ~info:(Info.v "remove")) |> Result.get_ok

module Stubs (I : Cstubs_inverted.INTERNAL) = struct
  let export ?(lock = false) name t f =
    I.internal ~runtime_lock:lock ("irmin_" ^ name) t f

  let () =
    export "key"
      (schema @-> ptr string @-> int @-> returning key)
      (fun schema arr i ->
        let arr = CArray.from_ptr arr i in
        let (module Store : Irmin.S), _ = Root.get schema in
        let l = CArray.to_list arr in
        let l =
          List.map
            (fun x -> Irmin.Type.of_string Store.step_t x |> Result.get_ok)
            l
        in
        Store.Key.v l |> Root.create)

  let () = export "type_unit" (void @-> returning ty) type_unit

  let () = export "value_unit" (void @-> returning value) value_unit

  let () = export "type_bool" (void @-> returning ty) type_bool

  let () = export "value_bool" (bool @-> returning value) value_bool

  let () = export "type_int" (void @-> returning ty) type_int

  let () = export "value_int" (int @-> returning value) value_int

  let () = export "type_string" (void @-> returning ty) type_string

  let () = export "value_string" (string @-> returning value) value_string

  let () = export "type_free" (ty @-> returning void) free

  let () = export "value_free" (value @-> returning void) free

  let () = export "config_new" (schema @-> returning config) config_new

  let () = export "config_free" (config @-> returning void) free

  let () =
    export "config_set"
      (config @-> string @-> value @-> returning bool)
      config_set

  let () =
    export "schema_new"
      (string_opt @-> string_opt @-> string_opt @-> string_opt
     @-> returning schema)
      schema_new

  let () = export "schema_free" (schema @-> returning void) free

  let () = export "repo_new" (schema @-> config @-> returning repo) repo_new

  let () = export "repo_free" (repo @-> returning void) free

  let () = export "master" (schema @-> repo @-> returning store) master

  let () =
    export "of_branch"
      (schema @-> repo @-> string @-> returning store)
      of_branch

  let () = export "set" (store @-> key @-> value @-> returning bool) set

  let () = export "get" (store @-> key @-> returning value) get

  let () = export "free" (store @-> returning void) free
end
