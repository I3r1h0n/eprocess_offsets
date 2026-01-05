#include <Windows.h>
#include <stdio.h>


DWORD eprocessOffsets[5][6] = {
    {26100, 0x1d0, 0x1d8, 0x248, 0x2e0, 0x5fa}, // Change from 24H2
    {19041, 0x440, 0x448, 0x4b8, 0x550, 0x87a}, // Change from 20H1
    {18362, 0x2e8, 0x2f0, 0x360, 0x3f8, 0x6fa}, // Change from 19H1
    {15063, 0x2e0, 0x2e8, 0x358, 0x3f8, 0x6ca}, // Offsets change starting from 1703
    {0, 0x2e8, 0x2f0, 0x358, 0x3f8, 0x6c2},     // Basic offsets begining from 1507
};

BOOL GetSystemBuild(DWORD* CurrentBuild) {
    char value[16];
    DWORD BufferSize = 16;

    LSTATUS status = RegGetValueA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CurrentBuild", RRF_RT_REG_SZ, NULL, (PVOID)&value, &BufferSize);
    if (status != ERROR_SUCCESS) {
        printf("[!] Can't read registry key!\n");
        exit(-1);
    }

    *CurrentBuild = strtoul(value, NULL, 10);
    return TRUE;
}

int ObtainOffsets(DWORD* offsets) {
    DWORD ubr;
    DWORD CurrentBuild;
    DWORD TokenOffset;
    DWORD ActiveProcessLinkOffset;
    DWORD UniqueProcessIdOffset;

    // Obtain system build
    GetSystemBuild(&CurrentBuild);
    printf("[*] CurrentBuild: %i\n", CurrentBuild);

    // Get offset from table
    for (int i = 0; i < 5; i++) {
        if (eprocessOffsets[i][0] > CurrentBuild) {
            continue;
        }
        else {
            offsets[0] = eprocessOffsets[i][1];
            offsets[1] = eprocessOffsets[i][2];
            offsets[2] = eprocessOffsets[i][3];
            offsets[3] = eprocessOffsets[i][4];
            offsets[4] = eprocessOffsets[i][5];
            return 0;
        }
    }

    // If CurrentBuild is too low
    offsets[0] = eprocessOffsets[3][1];
    offsets[1] = eprocessOffsets[3][2];
    offsets[2] = eprocessOffsets[3][3];
    offsets[3] = eprocessOffsets[3][4];
    offsets[4] = eprocessOffsets[3][5];

    return 0;
}

int main() {
    printf("[*] _EPROCESS offsets\n");

    // Get offsets in this order:
    // { PID, ActiveProcessLinks, Token, PEB, Protection }
    DWORD offsets[5] = { NULL };
    ObtainOffsets(offsets);

    // Print offsets
    printf("[*] PID: 0x%llx\n", offsets[0]);
    printf("[*] ActiveProcessList: 0x%llx\n", offsets[1]);
    printf("[*] Token: 0x%llx\n", offsets[2]);
    printf("[*] PEB: 0x%llx\n", offsets[3]);
    printf("[*] Protection: 0x%llx\n", offsets[4]);

    return 0;
}
