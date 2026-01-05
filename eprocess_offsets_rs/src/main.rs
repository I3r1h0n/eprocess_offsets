use std::ptr::null_mut;
use std::process::exit;
use winapi::{
    shared::minwindef::DWORD, 
    um::{
        winnt::PVOID, 
        winreg::{
            HKEY_LOCAL_MACHINE, 
            RRF_RT_REG_SZ, 
            RegGetValueA
        }
    }
};


const EPROCESS_OFFSETS: [[DWORD; 6]; 5] = [
    [26100, 0x1d0, 0x1d8, 0x248, 0x2e0, 0x5fa], // Change from 24H2
    [19041, 0x440, 0x448, 0x4b8, 0x550, 0x87a], // Change from 20H1
    [18362, 0x2e8, 0x2f0, 0x360, 0x3f8, 0x6fa], // Change from 19H1
    [15063, 0x2e0, 0x2e8, 0x358, 0x3f8, 0x6ca], // Offsets change starting from 1703
    [0,     0x2e8, 0x2f0, 0x358, 0x3f8, 0x6c2], // Basic offsets beginning from 1507
];

fn get_system_build() -> DWORD {
    let mut value: [u8; 16] = [0; 16];
    let mut buffer_size: DWORD = 16;

    let status = unsafe {
        RegGetValueA(
            HKEY_LOCAL_MACHINE,
            "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\0".as_ptr() as _,
            "CurrentBuild\0".as_ptr() as _,
            RRF_RT_REG_SZ,
            null_mut(),
            value.as_mut_ptr() as PVOID,
            &mut buffer_size,
        )
    };

    if status != 0 {
        println!("[!] Can't read registry key!");
        exit(-1);
    }

    let null_pos = value.iter().position(|&c| c == 0).unwrap_or(value.len());
    let build_str = String::from_utf8_lossy(&value[..null_pos]);
    
    build_str.parse::<DWORD>().unwrap_or(0)
}

fn obtain_offsets() -> [DWORD; 5] {
    let current_build = get_system_build();
    println!("[*] CurrentBuild: {}", current_build);

    for row in EPROCESS_OFFSETS.iter() {
        let build_number = row[0];
        if build_number > current_build {
            continue;
        }
        
        return [row[1], row[2], row[3], row[4], row[5]];
    }

    let fallback_row = &EPROCESS_OFFSETS[3];
    [fallback_row[1], fallback_row[2], fallback_row[3], fallback_row[4], fallback_row[5]]
}

fn main() {
    println!("[*] _EPROCESS offsets");
    let offsets = obtain_offsets();

    println!("[*] PID: 0x{:x}", offsets[0]);
    println!("[*] ActiveProcessList: 0x{:x}", offsets[1]);
    println!("[*] Token: 0x{:x}", offsets[2]);
    println!("[*] PEB: 0x{:x}", offsets[3]);
    println!("[*] Protection: 0x{:x}", offsets[4]);
}