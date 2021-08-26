module Schema = struct
  type metadata = [ `None | `Custom of string ]

  type contents =
    [ `String | `Json | `Json_value | `Type of string | `Custom of string ]

  type path = [ `String_list | `Custom of string ]

  type branch = [ `String | `Custom of string ]

  type hash =
    [ `Sha1
    | `Rmd160
    | `Sha224
    | `Sha256
    | `Sha384
    | `Sha512
    | `Blake2b
    | `Blake2s
    | `Custom of string ]

  let string_of_metadata = function
    | `None -> "Irmin.Metadata.None"
    | `Custom s -> s

  let string_of_contents = function
    | `String -> "Irmin.Contents.String"
    | `Json -> "Irmin.Contents.Json"
    | `Json_value -> "Irmin.Contents.Json_value"
    | `Type def ->
        Printf.sprintf
          "module type t = %s [@@deriving irmin] let merge = \
           Irmin.Merge.(option (idempotent t))"
          def
    | `Custom s -> s

  let string_of_path = function
    | `String_list -> "Irmin.Path.String_list"
    | `Custom s -> s

  let string_of_branch = function
    | `String -> "Irmin.Branch.String"
    | `Custom s -> s

  let string_of_hash = function
    | `Sha1 -> "Irmin.Hash.SHA1"
    | `Rmd160 -> "Irmin.Hash.RMD160"
    | `Sha224 -> "Irmin.Hash.SHA224"
    | `Sha256 -> "Imrin.Hash.SHA256"
    | `Sha384 -> "Irmin.Hash.SHA384"
    | `Sha512 -> "Irmin.Hash.SHA512"
    | `Blake2b -> "Irmin.Hash.BLAKE2B"
    | `Blake2s -> "Irmin.Hash.BLAKE2S"
    | `Custom s -> s

  type t = {
    metadata : metadata;
    contents : contents;
    path : path;
    branch : branch;
    hash : hash;
  }

  let template { metadata; contents; path; branch; hash } =
    Printf.sprintf
      {|  module Info = Irmin.Info.Default
  module Metadata = %s
  module Contents = %s
  module Path = %s
  module Branch = %s
  module Hash = %s
  module Node = Irmin.Node.Make(Hash)(Path)(Metadata)
  module Commit = Irmin.Commit.Make(Hash) |}
      (string_of_metadata metadata)
      (string_of_contents contents)
      (string_of_path path) (string_of_branch branch) (string_of_hash hash)

  let v ~metadata ~contents ~path ~branch ~hash =
    { metadata; contents; path; branch; hash }
end

module Store = struct
  type backend = [ `Mem | `Git_unix | `Fs | `Pack of int * int ]

  type t = { backend : backend; schema : Schema.t }

  let v backend schema = { backend; schema }

  let maker { backend; _ } =
    match backend with
    | `Mem -> "Irmin_mem"
    | `Git_unix -> "Irmin_unix.Git.FS"
    | `Fs -> "Irmin_unix.FS"
    | `Pack (version, i) ->
        Printf.sprintf "Irmin_pack.Maker (struct let version = `V%d end) (struct let entries = \
         %d let stable_hash = %d end)" version i i

  let template { backend; schema } =
    Printf.sprintf
      {|
module Schema = struct
%s
end
module Maker = %s
module Store = Maker.Make(Schema)
    |}
      (Schema.template schema)
      (maker { backend; schema })
end

let format filename =
  Unix.system (Printf.sprintf "ocamlformat --inplace '%s'" filename)

let metadata = `None

let contents = `String

let path = `String_list

let branch = `String

let hash = `Blake2b

let schema = Schema.v ~metadata ~contents ~path ~branch ~hash

let store = Store.v (`Pack (2, 32)) schema

let () = Store.template store |> print_endline
