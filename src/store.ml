module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "path"
      (repo @-> ptr string_opt @-> returning path)
      (fun (type repo) repo arr ->
        catch' (fun () ->
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
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let length = get_length length s in
            let s = string_from_ptr s ~length in
            match Irmin.Type.of_string Store.Path.t s with
            | Ok p -> Root.create_path (module Store) p
            | Error (`Msg e) ->
                Util.error_msg := Some e;
                null))

  let () =
    fn "path_empty"
      (repo @-> returning path)
      (fun (type repo) repo ->
        catch' (fun () ->
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
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let path = Root.get_path (module Store) p in
            let path = Store.Path.rdecons path |> Option.map fst in
            match path with
            | Some p -> Root.create_path (module Store) p
            | None -> null))

  let () =
    fn "path_append"
      (repo @-> path @-> ptr char @-> int64_t @-> returning path)
      (fun (type repo) repo p s length ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let length = get_length length s in
            let path = Root.get_path (module Store) p in
            let s = string_from_ptr s ~length in
            match Irmin.Type.of_string Store.step_t s with
            | Ok s -> Root.create_path (module Store) (Store.Path.rcons path s)
            | Error (`Msg e) ->
                let () = Util.error_msg := Some e in
                null))

  let () =
    fn "path_append_path"
      (repo @-> path @-> path @-> returning path)
      (fun (type repo) repo p s ->
        catch' (fun () ->
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
  let () = fn "hash_free" (hash @-> returning void) free

  let () =
    fn "hash_equal"
      (repo @-> hash @-> hash @-> returning bool)
      (fun (type repo) repo a b ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let a = Root.get_hash (module Store) a in
            let b = Root.get_hash (module Store) b in
            Irmin.Type.(unstage (equal Store.hash_t)) a b))

  let () =
    fn "contents_hash"
      (repo @-> value @-> returning hash)
      (fun (type repo) repo a ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let a = Root.get_contents (module Store) a in
            Root.create_hash (module Store) (Store.Contents.hash a)))

  let () =
    fn "contents_of_hash"
      (repo @-> hash @-> returning value)
      (fun (type repo) repo a ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), repo
                =
              Root.get_repo repo
            in
            let a = Root.get_hash (module Store) a in
            let c = run @@ Store.Contents.of_hash repo a in
            match c with
            | Some c -> Root.create_contents (module Store) c
            | None -> null))

  let () =
    fn "hash_to_string"
      (repo @-> hash @-> returning irmin_string)
      (fun (type repo) repo hash ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let hash = Root.get_hash (module Store) hash in
            let s = Irmin.Type.to_string Store.hash_t hash in
            Root.create_string s))

  let () =
    fn "hash_of_string"
      (repo @-> ptr char @-> int64_t @-> returning hash)
      (fun (type repo) repo s length ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), _ =
              Root.get_repo repo
            in
            let length = get_length length s in
            let s = string_from_ptr s ~length in
            let hash = Irmin.Type.of_string Store.Hash.t s in
            match hash with
            | Ok p -> Root.create_hash (module Store) p
            | Error (`Msg e) ->
                let () = Util.error_msg := Some e in
                null))

  let () =
    fn "main"
      (repo @-> returning store)
      (fun (type repo) repo ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), repo
                =
              Root.get_repo repo
            in
            Root.create_store
              (module Store)
              ( (module Store : Irmin.Generic_key.S with type t = Store.t),
                run (Store.main repo) )))

  let () =
    fn "of_branch"
      (repo @-> string @-> returning store)
      (fun (type repo) repo name ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type repo = repo), repo
                =
              Root.get_repo repo
            in
            match Irmin.Type.of_string Store.Branch.t name with
            | Error _ -> null
            | Ok branch ->
                Root.create_store
                  (module Store)
                  ( (module Store : Irmin.Generic_key.S with type t = Store.t),
                    run (Store.of_branch repo branch) )))

  let () =
    fn "get_head"
      (store @-> returning commit)
      (fun (type t) store ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let commit = run (Store.Head.find store) in
            match commit with
            | None -> null
            | Some x -> Root.create_commit (module Store) x))

  let () =
    fn "set_head"
      (store @-> commit @-> returning void)
      (fun (type t) store commit ->
        catch () (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let commit : Store.commit = Root.get_commit (module Store) commit in
            run (Store.Head.set store commit)))

  let () =
    fn "fast_forward"
      (store @-> commit @-> returning bool)
      (fun (type t) store commit ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let commit : Store.commit = Root.get_commit (module Store) commit in
            let res = run (Store.Head.fast_forward store commit) in
            match res with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Store.ff_error_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "merge_with_branch"
      (store @-> string @-> info @-> returning bool)
      (fun (type t) store branch info ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let info = Root.get_info (module Store) info in
            let branch =
              Irmin.Type.of_string Store.branch_t branch |> Result.get_ok
            in
            let res =
              run (Store.merge_with_branch store branch ~info:(fun () -> info))
            in
            match res with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Irmin.Merge.conflict_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "merge_with_commit"
      (store @-> commit @-> info @-> returning bool)
      (fun (type t) store commit info ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let info = Root.get_info (module Store) info in
            let commit = Root.get_commit (module Store) commit in
            let res =
              run (Store.merge_with_commit store commit ~info:(fun () -> info))
            in
            match res with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Irmin.Merge.conflict_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "merge_into"
      (store @-> store @-> info @-> returning bool)
      (fun (type t) store store1 info ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let (module Store1 : Irmin.Generic_key.S with type t = t), store1 =
              Root.get_store store1
            in
            let info = Root.get_info (module Store) info in
            let res =
              run (Store.merge_into ~into:store store1 ~info:(fun () -> info))
            in
            match res with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Irmin.Merge.conflict_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "set"
      (store @-> path @-> value @-> info @-> returning bool)
      (fun (type t) store path value info ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let info = Root.get_info (module Store) info in
            let path : Store.path = Root.get_path (module Store) path in
            let value : Store.contents =
              Root.get_contents (module Store) value
            in
            let x = run (Store.set store path value ~info:(fun () -> info)) in
            match x with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Store.write_error_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "test_and_set"
      (store @-> path @-> value @-> value @-> info @-> returning bool)
      (fun (type t) store path test set info ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let info = Root.get_info (module Store) info in
            let path : Store.path = Root.get_path (module Store) path in
            let test : Store.contents option =
              if test = null then None
              else Some (Root.get_contents (module Store) test)
            in
            let set : Store.contents option =
              if set = null then None
              else Some (Root.get_contents (module Store) set)
            in
            let x =
              run
                (Store.test_and_set store path ~test ~set ~info:(fun () -> info))
            in
            match x with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Store.write_error_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "test_and_set_tree"
      (store @-> path @-> tree @-> tree @-> info @-> returning bool)
      (fun (type t) store path test set info ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let info = Root.get_info (module Store) info in
            let path : Store.path = Root.get_path (module Store) path in
            let test : Store.tree option =
              if test = null then None
              else Some (Root.get_tree (module Store) test)
            in
            let set : Store.tree option =
              if set = null then None
              else Some (Root.get_tree (module Store) set)
            in
            let x =
              run
                (Store.test_and_set_tree store path ~test ~set ~info:(fun () ->
                     info))
            in
            match x with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Store.write_error_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "set_tree"
      (store @-> path @-> tree @-> info @-> returning bool)
      (fun (type t) store path tree info ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let info : Store.info = Root.get_info (module Store) info in
            let path : Store.path = Root.get_path (module Store) path in
            let tree' : Store.tree = Root.get_tree (module Store) tree in
            let x =
              run (Store.set_tree store path tree' ~info:(fun () -> info))
            in
            match x with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Store.write_error_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "find"
      (store @-> path @-> returning value)
      (fun (type t) store path ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let path : Store.path = Root.get_path (module Store) path in
            let x = run (Store.find store path) in
            match x with
            | Some x -> Root.create_contents (module Store) x
            | None -> null))

  let () =
    fn "find_tree"
      (store @-> path @-> returning tree)
      (fun (type t) store path ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let path : Store.path = Root.get_path (module Store) path in
            let x : Store.tree option = run (Store.find_tree store path) in
            match x with
            | Some x -> Root.create_tree (module Store) x
            | None -> null))

  let () =
    fn "remove"
      (store @-> path @-> info @-> returning bool)
      (fun (type t) store path info ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let module Info = Irmin_unix.Info (Store.Info) in
            let info = Root.get_info (module Store) info in
            let path : Store.path = Root.get_path (module Store) path in
            match run (Store.remove store path ~info:(fun () -> info)) with
            | Ok () -> true
            | Error e ->
                let s = Irmin.Type.to_string Store.write_error_t e in
                let () = Util.error_msg := Some s in
                false))

  let () =
    fn "mem"
      (store @-> path @-> returning bool)
      (fun (type t) store path ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let path : Store.path = Root.get_path (module Store) path in
            run (Store.mem store path)))

  let () =
    fn "mem_tree"
      (store @-> path @-> returning bool)
      (fun (type t) store path ->
        catch false (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let path : Store.path = Root.get_path (module Store) path in
            run (Store.mem_tree store path)))

  let () =
    fn "list"
      (store @-> path @-> returning path_list)
      (fun (type t) store path ->
        catch' (fun () ->
            let (module Store : Irmin.Generic_key.S with type t = t), store =
              Root.get_store store
            in
            let path : Store.path = Root.get_path (module Store) path in
            let items = run (Store.list store path) in
            let items = List.map (fun (k, _v) -> Store.Path.v [ k ]) items in
            Root.create_path_list (module Store) items))

  let () =
    fn "path_list_length"
      (path_list @-> returning uint64_t)
      (fun p ->
        catch UInt64.zero (fun () ->
            let arr = Root.get_path_list p in
            UInt64.of_int (CArray.length arr)))

  let () =
    fn "commit_list_length"
      (commit_list @-> returning uint64_t)
      (fun p ->
        catch UInt64.zero (fun () ->
            let arr = Root.get_commit_list p in
            UInt64.of_int (CArray.length arr)))

  let () =
    fn "path_list_get"
      (path_list @-> uint64_t @-> returning path)
      (fun p i ->
        let i = UInt64.to_int i in
        let arr = Root.get_path_list p in
        if i >= CArray.length arr then null
        else
          let x = CArray.unsafe_get arr i in
          Ctypes.Root.get x |> Ctypes.Root.create)

  let () =
    fn "commit_list_get"
      (commit_list @-> uint64_t @-> returning commit)
      (fun p i ->
        let i = UInt64.to_int i in
        let arr = Root.get_commit_list p in
        if i >= CArray.length arr then null
        else
          let x = CArray.unsafe_get arr i in
          Ctypes.Root.get x |> Ctypes.Root.create)

  let () =
    fn "path_list_free"
      (path_list @-> returning void)
      (fun p ->
        let arr = Root.get_path_list p in
        CArray.iter (fun x -> free x) arr;
        free p)

  let () =
    fn "commit_list_free"
      (commit_list @-> returning void)
      (fun p ->
        let arr = Root.get_commit_list p in
        CArray.iter (fun x -> free x) arr;
        free p)

  let () = fn "free" (store @-> returning void) free
end
