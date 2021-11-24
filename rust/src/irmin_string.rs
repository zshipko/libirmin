pub struct IrminString(pub *mut std::os::raw::c_char, pub i32);

extern "C" {
    fn free(_: *mut std::ffi::c_void);
}

impl Drop for IrminString {
    fn drop(&mut self) {
        unsafe { free(self.0 as *mut _) }
    }
}

impl IrminString {
    pub fn as_str(&self) -> &str {
        self.as_ref()
    }

    pub fn as_slice(&self) -> &[u8] {
        self.as_ref()
    }
}

impl PartialEq for IrminString {
    fn eq(&self, other: &IrminString) -> bool {
        self.as_slice() == other.as_slice()
    }
}

impl AsRef<[u8]> for IrminString {
    fn as_ref(&self) -> &[u8] {
        unsafe { std::slice::from_raw_parts_mut(self.0 as *mut u8, self.1 as usize) }
    }
}

impl AsRef<str> for IrminString {
    fn as_ref(&self) -> &str {
        unsafe {
            let s = std::slice::from_raw_parts_mut(self.0 as *mut u8, self.1 as usize);
            std::str::from_utf8_unchecked(s)
        }
    }
}

impl AsRef<std::ffi::CStr> for IrminString {
    fn as_ref(&self) -> &std::ffi::CStr {
        unsafe {
            let b = std::slice::from_raw_parts_mut(self.0 as *mut u8, self.1 as usize + 1);
            std::ffi::CStr::from_bytes_with_nul_unchecked(b)
        }
    }
}

impl Into<String> for IrminString {
    fn into(self) -> String {
        self.as_str().to_string()
    }
}

impl Into<Vec<u8>> for IrminString {
    fn into(self) -> Vec<u8> {
        self.as_slice().into()
    }
}
