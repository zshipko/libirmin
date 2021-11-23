fn main() {
    let path = std::env::current_dir().unwrap();

    if std::path::Path::new("Makefile").exists() {
        std::process::Command::new("make").spawn().unwrap();

        std::process::Command::new("cp")
            .arg("./libirmin.so")
            .arg("rust")
            .spawn()
            .unwrap();
    } else {
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
    };

    println!("cargo:rustc-link-lib=irmin");
    println!("cargo:rustc-link-search=.");
    println!("cargo:rustc-link-arg=-Wl,-rpath,{}", path.display());

    let header = if std::path::Path::new("irmin.h").exists() {
        "./irmin.h"
    } else {
        "../irmin.h"
    };

    // Tell cargo to invalidate the built crate whenever the wrapper changes
    println!("cargo:rerun-if-changed={}", header);

    let bindings = bindgen::builder()
        .header(header)
        .allowlist_type("Irmin.*")
        .allowlist_function("irmin.*")
        .generate()
        .unwrap();

    let out_path = std::path::PathBuf::from(std::env::var("OUT_DIR").unwrap());
    bindings.write_to_file(out_path.join("c.rs")).unwrap();
}
