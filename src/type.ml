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
    fn "type_json"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Contents.Json.t)

  let () =
    fn "type_json_value"
      (void @-> returning ty)
      (fun () -> Root.create Irmin.Contents.Json_value.t)

  let () =
    fn "type_path"
      (repo @-> returning ty)
      (fun repo ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        Root.create Store.path_t)

  let () =
    fn "type_commit"
      (repo @-> returning ty)
      (fun repo ->
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        Root.create (Store.commit_t repo))

  let () =
    fn "type_tree"
      (repo @-> returning ty)
      (fun repo ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        Root.create Store.tree_t)

  let () =
    fn "type_hash"
      (repo @-> returning ty)
      (fun repo ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        Root.create Store.hash_t)

  let () =
    fn "type_contents"
      (repo @-> returning ty)
      (fun repo ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        Root.create Store.contents_t)

  let () =
    fn "type_pair"
      (ty @-> ty @-> returning ty)
      (fun a b ->
        let a : 'a Irmin.Type.t = Root.get a in
        let b : 'b Irmin.Type.t = Root.get b in
        Root.create (Irmin.Type.pair a b))

  let () =
    fn "type_triple"
      (ty @-> ty @-> ty @-> returning ty)
      (fun a b c ->
        let a : 'a Irmin.Type.t = Root.get a in
        let b : 'b Irmin.Type.t = Root.get b in
        let c : 'c Irmin.Type.t = Root.get c in
        Root.create (Irmin.Type.triple a b c))

  let () =
    fn "type_name"
      (ty @-> ptr int @-> returning (ptr char))
      (fun ty len ->
        let ty = Root.get ty in
        let s = Fmt.to_to_string Irmin.Type.pp_ty ty in
        if not (is_null len) then len <-@ String.length s;
        malloc_string s)

  let () = fn "type_free" (ty @-> returning void) free
end
