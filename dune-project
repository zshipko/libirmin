(lang dune 2.0)

(generate_opam_files true)

(source (github zshipko/libirmin))
(license ISC)
(authors "Zach Shipko")
(maintainers "zachshipko@gmail.com")

(package
 (name libirmin)
 (synopsis "C bindings for irmin")
 (description "C bindings for irmin using Ctypes inverted stubs")
 (depends
  (dune (> 2.0))
  (ctypes (>= 0.19))
  (ctypes-foreign (>= 0.18))
  (irmin-unix (= "dev"))))

