#include "Machinegun.hpp"

int main() {
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
}
