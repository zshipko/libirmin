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

  let memcpy_ocaml_string t dest src n =
    coerce (ptr void) (ptr t)
    @@ Foreign.foreign "memcpy"
         (ptr t @-> ocaml_string @-> size_t @-> returning (ptr void))
         dest src n

  let malloc_string s =
    let len = String.length s in
    let m : char ptr = malloc char (Unsigned.Size_t.of_int (len + 1)) in
    let st = Ctypes.ocaml_string_start s in
    let _ = memcpy_ocaml_string char m st (Unsigned.Size_t.of_int len) in
    m +@ String.length s <-@ char_of_int 0;
    m

  let fn ?(lock = false) name t f =
    I.internal ~runtime_lock:lock ("irmin_" ^ name) t f

  let rec run x =
    Lwt.wakeup_paused ();
    match Lwt.poll x with
    | Some x -> x
    | None ->
        let () = Lwt_engine.iter true in
        run x
end
