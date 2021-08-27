open Ctypes

type config = Irmin.config

let config = ptr (typedef void "IrminConfig")

type 'a repo = 'a

let repo = ptr (typedef void "IrminRepo")

type 'a store = (module Irmin.S with type t = 'a) * 'a

let store = ptr (typedef void "Irmin")

type 'a ty = 'a Irmin.Type.t

let ty = ptr (typedef void "IrminType")

type 'a value = 'a

let value = ptr (typedef void "IrminValue")

type schema = Irmin_unix.Resolver.Store.t

let schema = ptr (typedef void "IrminSchema")

type 'a key = 'a

let key = ptr (typedef void "IrminKey")

type 'a tree = 'a

let tree = ptr (typedef void "IrminTree")

type 'a commit = 'a

let commit = ptr (typedef void "IrminCommit")

type 'a info = 'a

let info = ptr (typedef void "IrminInfo")
