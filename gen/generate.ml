let generate dirname =
  let prefix = "irmin" in
  let path basename = Filename.concat dirname basename in
  let ml_fd = open_out (path "irmin_bindings.ml") in
  let c_fd = open_out (path "irmin.c") in
  let h_fd = open_out (path "irmin.h") in
  let stubs = (module Bindings.Stubs : Cstubs_inverted.BINDINGS) in
  let writeln fd s = output_string fd (s ^ "\n") in
  begin
    (* Generate the ML module that links in the generated C. *)
    Cstubs_inverted.write_ml
      (Format.formatter_of_out_channel ml_fd) ~prefix stubs;

    (* Generate the C source file that exports OCaml functions. *)
    Format.fprintf (Format.formatter_of_out_channel c_fd)
    "#include \"irmin.h\"@\n%a"
      (Cstubs_inverted.write_c ~prefix) stubs;
    writeln c_fd "void irmin_init(char *argv[]){ caml_startup(argv);}";

    (* Generate the C header file that exports OCaml functions. *)
    writeln h_fd "#pragma once";
    writeln h_fd "typedef struct IrminContext IrminContext;";
    writeln h_fd "typedef struct IrminType IrminType;";
    writeln h_fd "typedef struct IrminValue IrminValue;";
    writeln h_fd "typedef struct IrminConfig IrminConfig;";
    writeln h_fd "typedef struct IrminRepo IrminRepo;";
    writeln h_fd "typedef struct Irmin Irmin;";
    writeln h_fd "void irmin_init(char *argv[]);";
    Cstubs_inverted.write_c_header
      (Format.formatter_of_out_channel h_fd) ~prefix stubs;

  end;
  close_out h_fd;
  close_out c_fd;
  close_out ml_fd

let () = generate (Sys.argv.(1))
