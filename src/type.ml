module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "type_unit"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Type.unit)

  let () =
    fn "type_bool"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Type.bool)

  let () =
    fn "type_int" (void @-> returning ty) (fun () -> Root.create Irmin.Type.int)

  let () =
    fn "type_string"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Type.string)

  let () =
    fn "type_bytes"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Type.bytes)

  let () =
    fn "type_list"
      (ty @-> returning ty)
      (fun elem ->
        let elem : 'a Irmin.Type.t = Root.get elem in
        Root.create (Irmin.Type.list elem))

  let () =
    fn "type_array"
      (ty @-> returning ty)
      (fun elem ->
        let elem : 'a Irmin.Type.t = Root.get elem in
        Root.create (Irmin.Type.array elem))

  let () =
    fn "type_option"
      (ty @-> returning ty)
      (fun elem ->
        let elem : 'a Irmin.Type.t = Root.get elem in
        Root.create (Irmin.Type.option elem))

  let () =
    fn "type_pair"
      (ty @-> returning ty)
      (fun elem ->
        let elem : 'a Irmin.Type.t = Root.get elem in
        Root.create (Irmin.Type.option elem))

  let () = fn "type_free" (ty @-> returning void) free
end
