module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "path"
      (schema @-> ptr string_opt @-> returning path)
      (fun schema arr ->
        let rec loop i acc =
          if is_null arr then acc
          else
            match !@(arr +@ i) with
            | None -> List.rev acc
            | Some x -> loop (i + 1) (x :: acc)
        in
        let l = loop 0 [] in
        let (module Store : Irmin.S), _ = Root.get schema in
        let l =
          List.map
            (fun x -> Irmin.Type.of_string Store.step_t x |> Result.get_ok)
            l
        in
        Store.Path.v l |> Root.create)

  let () = fn "path_free" (path @-> returning void) free

  let () =
    fn "main"
      (schema @-> repo @-> returning store)
      (fun schema repo ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let repo : Store.repo = Root.get repo in
        Root.create ((module Store : Irmin.S), Lwt_main.run (Store.main repo)))

  let () =
    fn "of_branch"
      (schema @-> repo @-> string @-> returning store)
      (fun schema repo name ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let repo : Store.repo = Root.get repo in
        match Irmin.Type.of_string Store.Branch.t name with
        | Error _ -> null
        | Ok branch ->
            Root.create
              ( (module Store : Irmin.S),
                Lwt_main.run (Store.of_branch repo branch) ))

  let () =
    fn "set"
      (store @-> path @-> value @-> info @-> returning bool)
      (fun store path value info ->
        let (module Store : Irmin.S), store = Root.get store in
        let info = Root.get info in
        let path : Store.path = Root.get path in
        let value : Store.contents = Root.get value in
        let x = Lwt_main.run (Store.set store path value ~info) in
        match x with Ok () -> true | Error _ -> false)

  let () =
    fn "get"
      (store @-> path @-> returning value)
      (fun store path ->
        let (module Store : Irmin.S), store = Root.get store in
        let path : Store.path = Root.get path in
        let x = Lwt_main.run (Store.find store path) in
        match x with Some x -> Root.create x | None -> null)

  let () =
    fn "remove"
      (store @-> path @-> info @-> returning void)
      (fun store path info ->
        let (module Store : Irmin.S), store = Root.get store in
        let module Info = Irmin_unix.Info (Store.Info) in
        let info = Root.get info in
        let path : Store.path = Root.get path in
        Lwt_main.run (Store.remove store path ~info) |> Result.get_ok)

  let () = fn "free" (store @-> returning void) free
end
