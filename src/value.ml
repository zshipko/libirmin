module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () = fn "value_unit" (void @-> returning value) (fun () -> Root.create ())

  let () = fn "value_int" (int @-> returning value) (fun i -> Root.create i)

  let () = fn "value_bool" (bool @-> returning value) (fun b -> Root.create b)

  let () =
    fn "value_string" (string @-> returning value) (fun s -> Root.create s)

  let () =
    fn "value_string_len"
      (ptr char @-> int @-> returning value)
      (fun s length ->
        let length = if length < 0 then strlen s else length in
        Root.create (string_from_ptr s ~length))

  let () =
    fn "value_to_string"
      (ty @-> value @-> ptr int @-> returning string)
      (fun ty value len ->
        let t = Root.get ty in
        let v = Root.get value in
        let s = Irmin.Type.to_string t v in
        if not (is_null len) then len <-@ String.length s;
        s)

  let () =
    fn "value_get_string"
      (value @-> ptr int @-> returning string)
      (fun value length ->
        let s = Root.get value in
        let len = String.length s in
        if not (is_null length) then length <-@ len;
        s)

  let () = fn "value_get_int" (value @-> returning int) Root.get

  let () = fn "value_get_bool" (value @-> returning bool) Root.get

  let () =
    fn "value_bytes"
      (string @-> returning value)
      (fun s -> Root.create (Bytes.of_string s))

  let () =
    fn "value_bytes_len"
      (ptr char @-> int @-> returning value)
      (fun s length ->
        let length = if length < 0 then strlen s else length in
        Root.create (Bytes.of_string (string_from_ptr s ~length)))

  let () =
    fn "value_list_new" (void @-> returning value) (fun () -> Root.create [])

  let () =
    fn "value_list_add"
      (value @-> value @-> returning void)
      (fun (type a) list x ->
        let tl : a list = Root.get list in
        let hd : a = Root.get x in
        Root.set list (hd :: tl))

  let () =
    fn "value_list_hd"
      (value @-> returning value)
      (fun list ->
        let list = Root.get list in
        match list with [] -> null | list -> Root.create (List.hd list))

  let () =
    fn "value_list_tl"
      (value @-> returning value)
      (fun list ->
        let list = Root.get list in
        Root.create (List.tl list))

  let () =
    fn "value_array_new"
      (int @-> value @-> returning value)
      (fun i x ->
        let x = Root.get x in
        Root.create (Array.make i x))

  let () =
    fn "value_array_set"
      (value @-> int @-> value @-> returning void)
      (fun (type a) arr i x ->
        let arr : a array = Root.get arr in
        let x : a = Root.get x in
        arr.(i) <- x)

  let () =
    fn "value_array_get"
      (value @-> int @-> returning value)
      (fun (type a) arr i ->
        let arr : a array = Root.get arr in
        Root.create arr.(i))

  let () =
    fn "value_option"
      (value @-> returning value)
      (fun value ->
        if is_null value then Root.create None
        else
          let x = Root.get value in
          Root.create (Some x))

  let () =
    fn "value_pair"
      (value @-> value @-> returning value)
      (fun a b ->
        let a = Root.get a in
        let b = Root.get b in
        Root.create (a, b))

  let () =
    fn "value_triple"
      (value @-> value @-> value @-> returning value)
      (fun a b c ->
        let a = Root.get a in
        let b = Root.get b in
        let c = Root.get c in
        Root.create (a, b, c))

  let () =
    fn "value_of_string"
      (ty @-> ptr char @-> int @-> returning value)
      (fun ty s length ->
        let length = if length < 0 then strlen s else length in
        let ty = Root.get ty in
        let s = string_from_ptr s ~length in
        match Irmin.Type.(of_string ty) s with
        | Ok x -> Root.create x
        | Error _ -> null)

  let () =
    fn "value_to_bin"
      (value @-> ptr int @-> returning string)
      (fun value len ->
        let t, v = Root.get value in
        let s = Irmin.Type.(unstage (to_bin_string t)) v in
        if not (is_null len) then len <-@ String.length s;
        s)

  let () =
    fn "value_of_bin"
      (ty @-> ptr char @-> int @-> returning value)
      (fun ty s length ->
        let length = if length < 0 then strlen s else length in
        let ty = Root.get ty in
        let s = string_from_ptr s ~length in
        match Irmin.Type.(unstage (of_bin_string ty)) s with
        | Ok x -> Root.create x
        | Error _ -> null)

  let () = fn "value_free" (value @-> returning void) free
end
