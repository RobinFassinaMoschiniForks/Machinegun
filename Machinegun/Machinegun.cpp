#include "Machinegun.hpp"

int main() {
	PVOID allocatedAddress = NULL;
	PVOID args[MAX_ARGS];
	SetArgs(5, args, NULL, 0x1000, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	MachineGunResult result = MachineGun(4, &allocatedAddress, L"kernel32.dll", "VirtualAlloc", args);

	if (result == SUCCESS) {
		std::cout << "Allocated address: " << std::hex << allocatedAddress << std::endl;
	}
}
