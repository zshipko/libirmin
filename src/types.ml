open Ctypes

type config = Irmin.config

let config = ptr (typedef void "IrminConfig")

let repo = ptr (typedef void "IrminRepo")

type 'a store = (module Irmin.S with type t = 'a) * 'a

let store = ptr (typedef void "Irmin")

let ty = ptr (typedef void "IrminType")

let value = ptr (typedef void "IrminValue")

type schema = Irmin_unix.Resolver.Store.t

let schema = ptr (typedef void "IrminSchema")

let path = ptr (typedef void "IrminPath")

let tree = ptr (typedef void "IrminTree")

let commit = ptr (typedef void "IrminCommit")

let hash = ptr (typedef void "IrminHash")

let info = ptr (typedef void "IrminInfo")
