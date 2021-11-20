module Make (I : Cstubs_inverted.INTERNAL) = struct
  include Ctypes
  include Types

  let find_config_key config name =
    Irmin.Backend.Conf.Spec.find_key (Irmin.Backend.Conf.spec config) name

  let type_name x = Fmt.to_to_string Irmin.Type.pp_ty x

  let free store = if not (is_null store) then Root.release store

  let strlen ptr =
    let rec loop i = if !@(ptr +@ i) = char_of_int 0 then i else loop (i + 1) in
    loop 0

  let malloc t n =
    coerce (ptr void) (ptr t)
    @@ Foreign.foreign "malloc" (size_t @-> returning (ptr void)) n

  let malloc_string s =
    let m = malloc char (Unsigned.Size_t.of_int @@ (String.length s + 1)) in
    for i = 0 to String.length s - 1 do
      m +@ i <-@ s.[i]
    done;
    m +@ String.length s <-@ char_of_int 0;
    m

  let fn ?(lock = false) name t f =
    I.internal ~runtime_lock:lock ("irmin_" ^ name) t f
end
