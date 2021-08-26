open Ctypes

let spec = Irmin.Private.Conf.Spec.v "test"

let config = ptr (typedef void "IrminConfig")

let repo = ptr (typedef void "IrminRepo")

let store = ptr (typedef void "Irmin")

let ty = ptr (typedef void "IrminType")

let value = ptr (typedef void "IrminValue")

let context = ptr (typedef void "IrminContext")

type context = (module Irmin.S) * Irmin.config

let type_unit () = Root.create Irmin.Type.unit

type 'a value = 'a Irmin.Type.t * 'a

let value_unit () = Root.create (Irmin.Type.unit, ())

let type_bool () = Root.create Irmin.Type.bool

let value_bool b = Root.create (Irmin.Type.bool, b)

let type_int () = Root.create Irmin.Type.int

let value_int i = Root.create (Irmin.Type.int, i)

let type_string () = Root.create Irmin.Type.string

let value_string s = Root.create (Irmin.Type.string, s)

let type_free t = Root.release t

let value_free v = Root.release v

let config_new context =
  let _, config = Root.get context in
  Root.create config

let config_free c = Root.release c

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
  let key = find_config_key key in
  let t, value = Root.get value in
  let config =
    match key with
    | None -> config
    | Some (Irmin.Private.Conf.K k) ->
        (* TODO: figure out a way to handle type mismatch *)
        if type_name t <> type_name (Irmin.Private.Conf.ty k) then config
        else Irmin.Private.Conf.add config k value
  in
  Root.set c config

let context_new store hash contents config_path =
  let hash = Option.map Irmin_unix.Resolver.Hash.find hash in
  Root.create
    (Irmin_unix.Resolver.load_config ?store ?hash ?contents ?config_path ())

let context_free c = Root.release c

module Stubs (I : Cstubs_inverted.INTERNAL) = struct
  let export name t f = I.internal ~runtime_lock:false ("irmin_" ^ name) t f

  let () = export "type_unit" (void @-> returning ty) type_unit

  let () = export "value_unit" (void @-> returning value) value_unit

  let () = export "type_bool" (void @-> returning ty) type_bool

  let () = export "value_bool" (bool @-> returning value) value_bool

  let () = export "type_int" (void @-> returning ty) type_int

  let () = export "value_int" (int @-> returning value) value_int

  let () = export "type_string" (void @-> returning ty) type_string

  let () = export "value_string" (string @-> returning value) value_string

  let () = export "type_free" (ty @-> returning void) type_free

  let () = export "value_free" (value @-> returning void) value_free

  let () = export "config_new" (context @-> returning config) config_new

  let () = export "config_free" (config @-> returning void) config_free

  let () =
    export "config_set"
      (config @-> string @-> value @-> returning void)
      config_set

  let () =
    export "context_new"
      (string_opt @-> string_opt @-> string_opt @-> string_opt
     @-> returning context)
      context_new

  let () = export "context_free" (context @-> returning void) context_free
end
