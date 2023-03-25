# Machinegun

![c++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![assembly](https://img.shields.io/badge/ASSEMBLY-ED8B00?style=for-the-badge&logo=Assembly&logoColor=white) ![windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

Machinegun is an advanced version of Metasploit's [railgun](https://docs.metasploit.com/docs/development/developing-modules/libraries/how-to-use-railgun-for-windows-post-exploitation.html).

Machinegun is capable of reliably running arbitrary Windows API functions on a remote computer and getting the results to the attacker's machine.

The project is still in its early stage and for it to be complete I need to implement:

- [ ] Organized API to work with.
- [ ] Stack to contain the variables.
- [ ] Proper exception handling.
- [ ] Support cross-compiling.

## Setup

For now, you will need [Visual Studio 2022](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16) but in the future, it will be with [CMake](https://cmake.org/) and cross-compiled with [Mingw](https://www.mingw-w64.org/).

## Basic Usage

```cpp
#include "Machinegun.hpp"

MachineGunResult result;
PVOID allocatedAddress = NULL;
PVOID args[MAX_ARGS];

result = SetArgs(4, args, NULL, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

if (result == SUCCESS) {
    result = MachineGun(4, &allocatedAddress, L"kernel32.dll", "VirtualAlloc", args);

    if (result == SUCCESS) {
        std::cout << "Allocated address: " << std::hex << allocatedAddress << std::endl;
    }
}
```
