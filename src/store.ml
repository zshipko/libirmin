module Make (I : Cstubs_inverted.INTERNAL) = struct
  open Util.Make (I)

  let () =
    fn "key"
      (schema @-> ptr string_opt @-> returning key)
      (fun schema arr ->
        let rec loop i acc =
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
        Store.Key.v l |> Root.create)

  let () =
    fn "master"
      (schema @-> repo @-> returning store)
      (fun schema repo ->
        let (module Store : Irmin.S), _, _ =
          Root.get schema |> Irmin_unix.Resolver.Store.destruct
        in
        let repo : Store.repo = Root.get repo in
        Root.create ((module Store : Irmin.S), Lwt_main.run (Store.master repo)))

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
      (store @-> key @-> value @-> info @-> returning bool)
      (fun store key value info ->
        let (module Store : Irmin.S), store = Root.get store in
        let info = Root.get info in
        let key : Store.key = Root.get key in
        let value : Store.contents = Root.get value in
        let x = Lwt_main.run (Store.set store key value ~info) in
        match x with Ok () -> true | Error _ -> false)

  let () =
    fn "get"
      (store @-> key @-> returning value)
      (fun store key ->
        let (module Store : Irmin.S), store = Root.get store in
        let key : Store.key = Root.get key in
        let x = Lwt_main.run (Store.find store key) in
        match x with Some x -> Root.create x | None -> null)

  let () =
    fn "remove"
      (store @-> key @-> info @-> returning void)
      (fun store key info ->
        let (module Store : Irmin.S), store = Root.get store in
        let module Info = Irmin_unix.Info (Store.Info) in
        let info = Root.get info in
        let key : Store.key = Root.get key in
        Lwt_main.run (Store.remove store key ~info) |> Result.get_ok)

  let () = fn "free" (store @-> returning void) free
end
