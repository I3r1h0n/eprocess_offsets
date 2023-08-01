# _EPROCESS offsets
List of eprocess offsets for UniqueProcessID, ActiveProcessList and Token values. 

| Windows Version            | Build Number | Token | Active Process Links | PID   |
|----------------------------|--------------|-------|----------------------|-------|
| Windows 11 22H2            | 22621        | 0x4b8 | 0x448                | 0x440 |
| Windows Sever 2022         | 20348        | 0x4b8 | 0x448                | 0x440 |
| Windows 11 21H2            | 22000        | 0x4b8 | 0x448                | 0x440 |
| Windows 11 Insider Preview | 22000        | 0x4b8 | 0x448                | 0x440 |
| Windows 11 21H2            | 19041        | 0x4b8 | 0x448                | 0x440 |
| Windows 11 21H1            | 19041        | 0x4b8 | 0x448                | 0x440 |
| Windows 10 20H2            | 19041        | 0x4b8 | 0x448                | 0x440 |
| Windows 10 20H1            | 19041        | 0x4b8 | 0x448                | 0x440 |
| Windows 10 19H2            | 18362        | 0x360 | 0x2f0                | 0x2e8 |
| Windows 10 19H1            | 18362        | 0x360 | 0x2f0                | 0x2e8 |
| Windows 10 1809            | 17763        | 0x358 | 0x2e8                | 0x2e0 |
| Windows 10 1803            | 17134        | 0x358 | 0x2e8                | 0x2e0 |
| Windows 10 1709            | 16299        | 0x358 | 0x2e8                | 0x2e0 |
| Windows 10 1703            | 15063        | 0x358 | 0x2e8                | 0x2e0 |
| Windows 10 1607            | 14393        | 0x358 | 0x2f0                | 0x2e8 |
| Windows 10 1511            | 10586        | 0x358 | 0x2f0                | 0x2e8 |
| Windows 10 1507            | 10240        | 0x358 | 0x2f0                | 0x2e8 |

_All info was taken from [vergilius project](https://www.vergiliusproject.com) and partly from [ntdiff](https://ntdiff.github.io). Big shout out to them._

I've also created a xlsx file, and made it colorful, so you can easier see all changes happend to eprocess offsets.

## Code part
In eprocess_offsets/ you can find my C implementation of eprocess offsets determinant. I've commented all code, so you can use it in your own projects!

~I3r1h0n~
