open Ctypes

let spec = Irmin.Private.Conf.Spec.v "test"

let irmin_type_unit () = Ctypes.Root.create Irmin.Type.unit
let irmin_value_unit () = Ctypes.Root.create ()

let irmin_type_bool () = Ctypes.Root.create Irmin.Type.bool
let irmin_value_bool b = Ctypes.Root.create b

let irmin_type_int () = Ctypes.Root.create Irmin.Type.int
let irmin_value_int i = Ctypes.Root.create i

let irmin_type_free t = Ctypes.Root.release t
let irmin_value_free v = Ctypes.Root.release v

let config_new () = Ctypes.Root.create (Irmin.Private.Conf.empty spec)
let config_free c = Ctypes.Root.release c

module Stubs (I : Cstubs_inverted.INTERNAL) = struct
  let config = ptr void
  let ty = ptr void
  let value = ptr void

  let () = I.internal ~runtime_lock:true "irmin_type_unit" (void @-> returning ty) irmin_type_unit
  let () = I.internal "irmin_value_unit" (void @-> returning value) irmin_value_unit

  let () = I.internal "irmin_type_bool" (void @-> returning ty) irmin_type_bool
  let () = I.internal "irmin_value_bool" (bool @-> returning value) irmin_value_bool

  let () = I.internal "irmin_type_int" (void @-> returning ty) irmin_type_int
  let () = I.internal "irmin_value_int" (int @-> returning value) irmin_value_int

  let () = I.internal "irmin_type_free" (ty @-> returning void) irmin_type_free
  let () = I.internal "irmin_value_free" (value @-> returning void) irmin_value_free

  let () = I.internal "config_new" (void @-> returning config) config_new
  let () = I.internal "config_free" (config @-> returning void) config_free
end
