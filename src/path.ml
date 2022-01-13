module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "path"
      (repo @-> ptr string_opt @-> returning path)
      (fun (type repo) repo arr ->
        catch' path (fun () ->
            let rec loop i acc =
              if is_null arr then acc
              else
                match !@(arr +@ i) with
                | None -> List.rev acc
                | Some x -> loop (i + 1) (x :: acc)
            in
            let l = loop 0 [] in
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let l =
              List.map
                (fun x -> Irmin.Type.of_string Store.step_t x |> Result.get_ok)
                l
            in
            Store.Path.v l |> Root.create_path (module Store)))

  let () =
    fn "path_of_string"
      (repo @-> ptr char @-> int64_t @-> returning path)
      (fun (type repo) repo s length ->
        catch' path (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let length = get_length length s in
            let s = string_from_ptr s ~length in
            match Irmin.Type.of_string Store.Path.t s with
            | Ok p -> Root.create_path (module Store) p
            | Error (`Msg e) ->
                Util.error_msg := Some e;
                null path))

  let () =
    fn "path_empty"
      (repo @-> returning path)
      (fun (type repo) repo ->
        catch' path (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            Root.create_path (module Store) Store.Path.empty))

  let () =
    fn "path_to_string"
      (repo @-> path @-> returning irmin_string)
      (fun (type repo) repo p ->
        let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
          Root.get_repo repo
        in
        let path = Root.get_path (module Store) p in
        let s = Irmin.Type.to_string Store.Path.t path in
        Root.create_string s)

  let () =
    fn "path_parent"
      (repo @-> path @-> returning path)
      (fun (type repo) repo p ->
        catch' path (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let p = Root.get_path (module Store) p in
            let p = Store.Path.rdecons p |> Option.map fst in
            match p with
            | Some p -> Root.create_path (module Store) p
            | None -> null path))

  let () =
    fn "path_append"
      (repo @-> path @-> ptr char @-> int64_t @-> returning path)
      (fun (type repo) repo p s length ->
        catch' path (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let length = get_length length s in
            let p = Root.get_path (module Store) p in
            let s = string_from_ptr s ~length in
            match Irmin.Type.of_string Store.step_t s with
            | Ok s -> Root.create_path (module Store) (Store.Path.rcons p s)
            | Error (`Msg e) ->
                let () = Util.error_msg := Some e in
                null path))

  let () =
    fn "path_append_path"
      (repo @-> path @-> path @-> returning path)
      (fun (type repo) repo p s ->
        catch' path (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let rec concat_paths a b =
              match Store.Path.decons b with
              | Some (step, path) -> concat_paths (Store.Path.rcons a step) path
              | None -> a
            in
            let path = Root.get_path (module Store) p in
            let path' = Root.get_path (module Store) s in
            let dest = concat_paths path path' in
            Root.create_path (module Store) dest))

  let () =
    fn "path_equal"
      (repo @-> path @-> path @-> returning bool)
      (fun (type repo) repo a b ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let a = Root.get_path (module Store) a in
            let b = Root.get_path (module Store) b in
            Irmin.Type.(unstage (equal Store.path_t)) a b))

  let () = fn "path_free" (path @-> returning void) free
end
