fn main() {
    let path = std::env::current_dir().unwrap().canonicalize().unwrap();

    std::process::Command::new("make")
        .arg("-C")
        .arg("..")
        .spawn()
        .unwrap();

    std::process::Command::new("cp")
        .arg("../libirmin.so")
        .arg(".")
        .spawn()
        .unwrap();

    std::process::Command::new("cp")
        .arg("../irmin.h")
        .arg(".")
        .spawn()
        .unwrap();

    println!("cargo:rustc-link-lib=irmin");
    println!("cargo:rustc-link-search=.");
    println!("cargo:rustc-link-arg=-Wl,-rpath,{}", path.display());

    // Tell cargo to invalidate the built crate whenever the wrapper changes
    println!("cargo:rerun-if-changed=../irmin.h");

    let bindings = bindgen::builder()
        .header("../irmin.h")
        .allowlist_type("Irmin.*")
        .allowlist_function("irmin.*")
        .generate()
        .unwrap();

    let out_path = std::path::PathBuf::from(std::env::var("OUT_DIR").unwrap());
    bindings.write_to_file(out_path.join("c.rs")).unwrap();
}
