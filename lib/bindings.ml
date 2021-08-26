open Ctypes

let spec = Irmin.Private.Conf.Spec.v "test"

let config = ptr (typedef void "IrminConfig")

let repo = ptr (typedef void "IrminRepo")

let store = ptr (typedef void "Irmin")

let ty = ptr (typedef void "IrminType")

let value = ptr (typedef void "IrminValue")

let type_unit () = Root.create Irmin.Type.unit

let value_unit () = Root.create ()

let type_bool () = Root.create Irmin.Type.bool

let value_bool b = Root.create b

let type_int () = Root.create Irmin.Type.int

let value_int i = Root.create i

let type_string () = Root.create Irmin.Type.string

let value_string s = Root.create s

let type_free t = Root.release t

let value_free v = Root.release v

let config_new () = Root.create (Irmin.Private.Conf.empty spec)

let config_free c = Root.release c

let find_config_key name =
  let specs = Irmin.Private.Conf.Spec.list () in
  Seq.fold_left
    (fun acc spec ->
      match acc with
      | Some _ as x -> x
      | None -> Irmin.Private.Conf.Spec.find_key spec name)
    None specs

let config_set c key value =
  let config : Irmin.config = Root.get c in
  let key = find_config_key key in
  let config =
    match key with
    | None -> config
    | Some (Irmin.Private.Conf.K k) ->
        Irmin.Private.Conf.add config k (Root.get value)
  in
  Root.set c config

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

  let () = export "config_new" (void @-> returning config) config_new

  let () = export "config_free" (config @-> returning void) config_free

  let () =
    export "config_set"
      (config @-> string @-> value @-> returning void)
      config_set
end
