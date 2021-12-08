module Make (I : Cstubs_inverted.INTERNAL) = struct
  include Ctypes
  include Types
  include Unsigned

  let find_config_key config name =
    Irmin.Backend.Conf.Spec.find_key (Irmin.Backend.Conf.spec config) name

  let type_name x = Fmt.to_to_string Irmin.Type.pp_ty x

  let free store = if not (is_null store) then Ctypes.Root.release store

  let strlen ptr =
    if is_null ptr then 0
    else
      let rec loop i =
        if !@(ptr +@ i) = char_of_int 0 then i else loop (i + 1)
      in
      loop 0

  let get_length length s =
    let length = Int64.to_int length in
    if length < 0 then strlen s else length

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

  module Root = struct
    let get_repo (type a) x : a repo = Root.get x

    let create_repo (type a) (module S : Irmin.Generic_key.S with type repo = a)
        (r : a repo) =
      Root.create r

    let get_store (type a) x : a store = Root.get x

    let create_store (type a) (module S : Irmin.Generic_key.S with type t = a)
        (r : a store) =
      Root.create r

    let get_config x : config = Root.get x

    let create_config (r : config) = Root.create r

    let set_config ptr (x : config) = Root.set ptr x

    let get_ty x : 'a Irmin.Type.t = Root.get x

    let create_ty (x : 'a Irmin.Type.t) = Root.create x

    let get_value x : 'a = Root.get x

    let set_value ptr x = Root.set ptr x

    let create_value (x : 'a) = Root.create x

    let get_path (type a)
        (module S : Irmin.Generic_key.S with type Schema.Path.t = a) x : S.path
        =
      Root.get x

    let create_path (type a)
        (module S : Irmin.Generic_key.S with type Schema.Path.t = a)
        (r : S.path) =
      Root.create r

    let get_hash (type a)
        (module S : Irmin.Generic_key.S with type Schema.Hash.t = a) x : S.hash
        =
      Root.get x

    let create_hash (type a)
        (module S : Irmin.Generic_key.S with type Schema.Hash.t = a)
        (r : S.hash) =
      Root.create r

    let get_tree (type a) (module S : Irmin.Generic_key.S with type tree = a) x
        : S.tree =
      Root.get x

    let create_tree (type a) (module S : Irmin.Generic_key.S with type tree = a)
        (r : S.tree) =
      Root.create r

    let set_tree (type a) (module S : Irmin.Generic_key.S with type tree = a)
        ptr (r : S.tree) =
      Root.set ptr r

    let get_commit (type a)
        (module S : Irmin.Generic_key.S with type commit = a) x : S.commit =
      Root.get x

    let create_commit (type a)
        (module S : Irmin.Generic_key.S with type commit = a) (r : S.commit) =
      Root.create r

    let get_contents (type a)
        (module S : Irmin.Generic_key.S with type Schema.Contents.t = a) x :
        S.contents =
      Root.get x

    let create_contents (type a)
        (module S : Irmin.Generic_key.S with type Schema.Contents.t = a)
        (r : S.contents) =
      Root.create r

    let get_info (type a)
        (module S : Irmin.Generic_key.S with type Schema.Info.t = a) x : S.info
        =
      Root.get x

    let set_info (type a)
        (module S : Irmin.Generic_key.S with type Schema.Info.t = a) ptr
        (x : S.info) : unit =
      Root.set ptr x

    let create_info (type a)
        (module S : Irmin.Generic_key.S with type Schema.Info.t = a)
        (r : S.info) =
      Root.create r
  end
end
