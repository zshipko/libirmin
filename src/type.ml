module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "type_unit"
      (void @-> returning ty)
      (fun () -> Root.create_ty Irmin.Type.unit)

  let () =
    fn "type_bool"
      (void @-> returning ty)
      (fun () -> Root.create_ty Irmin.Type.bool)

  let () =
    fn "type_int"
      (void @-> returning ty)
      (fun () -> Root.create_ty Irmin.Type.int)

  let () =
    fn "type_float"
      (void @-> returning ty)
      (fun () -> Root.create_ty Irmin.Type.float)

  let () =
    fn "type_string"
      (void @-> returning ty)
      (fun () -> Root.create_ty Irmin.Type.string)

  let () =
    fn "type_bytes"
      (void @-> returning ty)
      (fun () -> Root.create_ty Irmin.Type.bytes)

  let () =
    fn "type_list"
      (ty @-> returning ty)
      (fun elem ->
        let elem : 'a Irmin.Type.t = Root.get_ty elem in
        Root.create_ty (Irmin.Type.list elem))

  let () =
    fn "type_array"
      (ty @-> returning ty)
      (fun elem ->
        let elem : 'a Irmin.Type.t = Root.get_ty elem in
        Root.create_ty (Irmin.Type.array elem))

  let () =
    fn "type_option"
      (ty @-> returning ty)
      (fun elem ->
        let elem : 'a Irmin.Type.t = Root.get_ty elem in
        Root.create_ty (Irmin.Type.option elem))

  let () =
    fn "type_json"
      (void @-> returning ty)
      (fun () -> Root.create_ty Irmin.Contents.Json.t)

  let () =
    fn "type_json_value"
      (void @-> returning ty)
      (fun () -> Root.create_ty Irmin.Contents.Json_value.t)

  let () =
    fn "type_path"
      (repo @-> returning ty)
      (fun (type repo) repo ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        Root.create_ty Store.path_t)

  let () =
    fn "type_commit"
      (repo @-> returning ty)
      (fun (type repo) repo ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), repo =
          Root.get_repo repo
        in
        Root.create_ty (Store.commit_t repo))

  let () =
    fn "type_tree"
      (repo @-> returning ty)
      (fun (type repo) repo ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        Root.create_ty Store.tree_t)

  let () =
    fn "type_hash"
      (repo @-> returning ty)
      (fun (type repo) repo ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        Root.create_ty Store.hash_t)

  let () =
    fn "type_contents"
      (repo @-> returning ty)
      (fun (type repo) repo ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        Root.create_ty Store.contents_t)

  let () =
    fn "type_pair"
      (ty @-> ty @-> returning ty)
      (fun a b ->
        let a : 'a Irmin.Type.t = Root.get_ty a in
        let b : 'b Irmin.Type.t = Root.get_ty b in
        Root.create_ty (Irmin.Type.pair a b))

  let () =
    fn "type_triple"
      (ty @-> ty @-> ty @-> returning ty)
      (fun a b c ->
        let a : 'a Irmin.Type.t = Root.get_ty a in
        let b : 'b Irmin.Type.t = Root.get_ty b in
        let c : 'c Irmin.Type.t = Root.get_ty c in
        Root.create_ty (Irmin.Type.triple a b c))

  let () =
    fn "type_name"
      (ty @-> returning irmin_string)
      (fun ty ->
        let ty = Root.get_ty ty in
        let s = Fmt.to_to_string Irmin.Type.pp_ty ty in
        Root.create_string s)

  let () =
    fn "type_diff"
      (ty @-> returning ty)
      (fun ty ->
        let ty = Root.get_ty ty in
        Root.create_ty (Irmin.Diff.t ty))

  let () = fn "type_free" (ty @-> returning void) free
end
