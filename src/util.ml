module Make (I : Cstubs_inverted.INTERNAL) = struct
  include Ctypes
  include Types

  let find_config_key config name =
    Irmin.Backend.Conf.Spec.find_key (Irmin.Backend.Conf.spec config) name

  let type_name x = Fmt.to_to_string Irmin.Type.pp_ty x

  let free store = Root.release store

  let strlen ptr =
    let rec loop i = if !@(ptr +@ i) = char_of_int 0 then i else loop (i + 1) in
    loop 0

  let fn ?(lock = false) name t f =
    I.internal ~runtime_lock:lock ("irmin_" ^ name) t f
end
