module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "path"
      (repo @-> ptr string_opt @-> returning path)
      (fun repo arr ->
        let rec loop i acc =
          if is_null arr then acc
          else
            match !@(arr +@ i) with
            | None -> List.rev acc
            | Some x -> loop (i + 1) (x :: acc)
        in
        let l = loop 0 [] in
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let l =
          List.map
            (fun x -> Irmin.Type.of_string Store.step_t x |> Result.get_ok)
            l
        in
        Store.Path.v l |> Root.create)

  let () =
    fn "path_of_string"
      (repo @-> ptr char @-> int @-> returning path)
      (fun repo s length ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let length = if length < 0 then strlen s else length in
        let s = string_from_ptr s ~length in
        match Irmin.Type.of_string Store.Path.t s with
        | Ok p -> Root.create p
        | Error _ -> null)

  let () =
    fn "path_to_string"
      (repo @-> path @-> ptr int @-> returning (ptr char))
      (fun repo p l ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let path = Root.get p in
        let s = Irmin.Type.to_string Store.Path.t path in
        if not (is_null l) then l <-@ String.length s;
        malloc_string s)

  let () =
    fn "path_parent"
      (repo @-> path @-> returning path)
      (fun repo p ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let path = Root.get p in
        let path = Store.Path.rdecons path |> Option.map fst in
        match path with Some p -> Root.create p | None -> null)

  let () =
    fn "path_append"
      (repo @-> path @-> ptr char @-> int @-> returning path)
      (fun repo p s length ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let path = Root.get p in
        let length = if length < 0 then strlen s else length in
        let s = string_from_ptr s ~length in
        let s = Irmin.Type.of_string Store.step_t s |> Result.get_ok in
        Root.create (Store.Path.rcons path s))

  let () =
    fn "path_equal"
      (repo @-> path @-> path @-> returning bool)
      (fun repo a b ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let a = Root.get a in
        let b = Root.get b in
        Irmin.Type.(unstage (equal Store.path_t)) a b)

  let () = fn "path_free" (path @-> returning void) free

  let () = fn "hash_free" (hash @-> returning void) free

  let () =
    fn "hash_equal"
      (repo @-> hash @-> hash @-> returning bool)
      (fun repo a b ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let a = Root.get a in
        let b = Root.get b in
        Irmin.Type.(unstage (equal Store.hash_t)) a b)

  let () =
    fn "contents_hash"
      (repo @-> value @-> returning hash)
      (fun repo a ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let a = Root.get a in
        Root.create (Store.Contents.hash a))

  let () =
    fn "contents_of_hash"
      (repo @-> hash @-> returning value)
      (fun repo a ->
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        let a = Root.get a in
        let c = run @@ Store.Contents.of_hash repo a in
        match c with Some c -> Root.create c | None -> null)

  let () =
    fn "hash_to_string"
      (repo @-> hash @-> ptr int @-> returning (ptr char))
      (fun repo hash l ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let hash = Root.get hash in
        let s = Irmin.Type.to_string Store.hash_t hash in
        if not (is_null l) then l <-@ String.length s;
        malloc_string s)

  let () =
    fn "hash_of_string"
      (repo @-> ptr char @-> int @-> returning hash)
      (fun repo s length ->
        let (module Store : Irmin.Generic_key.S), _ = Root.get repo in
        let s = string_from_ptr s ~length in
        let hash = Irmin.Type.of_string Store.Hash.t s in
        match hash with Ok p -> Root.create p | Error _ -> null)

  let () =
    fn "main"
      (repo @-> returning store)
      (fun repo ->
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        Root.create ((module Store : Irmin.Generic_key.S), run (Store.main repo)))

  let () =
    fn "of_branch"
      (repo @-> string @-> returning store)
      (fun repo name ->
        let (module Store : Irmin.Generic_key.S), repo = Root.get repo in
        match Irmin.Type.of_string Store.Branch.t name with
        | Error _ -> null
        | Ok branch ->
            Root.create
              ( (module Store : Irmin.Generic_key.S),
                run (Store.of_branch repo branch) ))

  let () =
    fn "get_head"
      (store @-> returning commit)
      (fun store ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let commit = run (Store.Head.find store) in
        match commit with None -> null | Some x -> Root.create x)

  let () =
    fn "set_head"
      (store @-> commit @-> returning void)
      (fun store commit ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let commit : Store.commit = Root.get commit in
        run (Store.Head.set store commit))

  let () =
    fn "fast_forward"
      (store @-> commit @-> returning bool)
      (fun store commit ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let commit : Store.commit = Root.get commit in
        let res = run (Store.Head.fast_forward store commit) in
        match res with Ok () -> true | Error _ -> false)

  let () =
    fn "merge_with_branch"
      (store @-> string @-> info @-> returning bool)
      (fun store branch info ->
        let info = Root.get info in
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let branch =
          Irmin.Type.of_string Store.branch_t branch |> Result.get_ok
        in
        let res =
          run (Store.merge_with_branch store branch ~info:(fun () -> info))
        in
        match res with Ok () -> true | Error _ -> false)

  let () =
    fn "merge_with_commit"
      (store @-> commit @-> info @-> returning bool)
      (fun store commit info ->
        let info = Root.get info in
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let commit = Root.get commit in
        let res =
          run (Store.merge_with_commit store commit ~info:(fun () -> info))
        in
        match res with Ok () -> true | Error _ -> false)

  let () =
    fn "set"
      (store @-> path @-> value @-> info @-> returning bool)
      (fun store path value info ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let info = Root.get info in
        let path : Store.path = Root.get path in
        let value : Store.contents = Root.get value in
        let x = run (Store.set store path value ~info:(fun () -> info)) in
        match x with Ok () -> true | Error _ -> false)

  let () =
    fn "test_and_set"
      (store @-> path @-> value @-> value @-> info @-> returning bool)
      (fun store path test set info ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let info = Root.get info in
        let path : Store.path = Root.get path in
        let test : Store.contents option =
          if test = null then None else Some (Root.get test)
        in
        let set : Store.contents option =
          if set = null then None else Some (Root.get set)
        in
        let x =
          run (Store.test_and_set store path ~test ~set ~info:(fun () -> info))
        in
        match x with Ok () -> true | Error _ -> false)

  let () =
    fn "test_and_set_tree"
      (store @-> path @-> tree @-> tree @-> info @-> returning bool)
      (fun store path test set info ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let info = Root.get info in
        let path : Store.path = Root.get path in
        let test : Store.tree option =
          if test = null then None else Some (Root.get test)
        in
        let set : Store.tree option =
          if set = null then None else Some (Root.get set)
        in
        let x =
          run
            (Store.test_and_set_tree store path ~test ~set ~info:(fun () ->
                 info))
        in
        match x with Ok () -> true | Error _ -> false)

  let () =
    fn "set_tree"
      (store @-> path @-> tree @-> info @-> returning bool)
      (fun store path tree info ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let info : Store.info = Root.get info in
        let path : Store.path = Root.get path in
        let tree' : Store.tree = Root.get tree in
        let x = run (Store.set_tree store path tree' ~info:(fun () -> info)) in
        match x with Ok () -> true | Error _ -> false)

  let () =
    fn "find"
      (store @-> path @-> returning value)
      (fun store path ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let path : Store.path = Root.get path in
        let x = run (Store.find store path) in
        match x with Some x -> Root.create x | None -> null)

  let () =
    fn "find_tree"
      (store @-> path @-> returning tree)
      (fun store path ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let path : Store.path = Root.get path in
        let x : Store.tree option = run (Store.find_tree store path) in
        match x with Some x -> Root.create x | None -> null)

  let () =
    fn "remove"
      (store @-> path @-> info @-> returning void)
      (fun store path info ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let module Info = Irmin_unix.Info (Store.Info) in
        let info = Root.get info in
        let path : Store.path = Root.get path in
        run (Store.remove store path ~info:(fun () -> info)) |> Result.get_ok)

  let () =
    fn "mem"
      (store @-> path @-> returning bool)
      (fun store path ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let path : Store.path = Root.get path in
        run (Store.mem store path))

  let () =
    fn "mem_tree"
      (store @-> path @-> returning bool)
      (fun store path ->
        let (module Store : Irmin.Generic_key.S), store = Root.get store in
        let path : Store.path = Root.get path in
        run (Store.mem_tree store path))

  let () = fn "free" (store @-> returning void) free
end
