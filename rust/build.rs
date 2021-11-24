fn main() {
    let path = std::env::var("CARGO_MANIFEST_DIR").unwrap();

    std::process::Command::new("make")
        .arg("-C")
        .arg(format!("{}/..", path))
        .spawn()
        .unwrap();

    std::process::Command::new("cp")
        .arg(format!("{}/../libirmin.so", path))
        .arg(&path)
        .spawn()
        .unwrap();

    let header = format!("{}/../irmin.h", path);

    /*std::process::Command::new("cp")
    .arg(&header)
    .arg(&path)
    .spawn()
    .unwrap();*/

    std::process::Command::new("ls").arg("..").spawn().unwrap();

    println!("cargo:rustc-link-lib=irmin");
    println!("cargo:rustc-link-search={}", path);
    println!(
        "cargo:rustc-link-arg=-Wl,-rpath,{} -Wl,-rpath,{}/../_build/default/lib",
        path, path
    );

    // Tell cargo to invalidate the built crate whenever the wrapper changes
    println!("cargo:rerun-if-changed={}", header);

    let bindings = bindgen::builder()
        .header(&header)
        .allowlist_type("Irmin.*")
        .allowlist_function("irmin.*")
        .generate()
        .unwrap();

    let out_path = std::path::PathBuf::from(std::env::var("OUT_DIR").unwrap());
    bindings.write_to_file(out_path.join("c.rs")).unwrap();
}
