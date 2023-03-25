#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include <iostream>
#include <stdarg.h>
#include <string>
#include <Windows.h>

constexpr int MAX_ARGS = 11;

struct MachineGunPkg {
	PVOID NumberOfArgs;
	PVOID Function;
	PVOID Arg1;
	PVOID Arg2;
	PVOID Arg3;
	PVOID Arg4;
	PVOID Arg5;
	PVOID Arg6;
	PVOID Arg7;
	PVOID Arg8;
	PVOID Arg9;
	PVOID Arg10;
	PVOID Arg11;
};

enum MachineGunResult {
	SUCCESS = 0,
	MODULE_NOT_FOUND,
	FUNCTION_NOT_FOUND,
	INVALID_ARGS_NUMBER
};

extern "C" PVOID MACHINEGUN_EXECUTE(PVOID machineGunPkg);

void SetArgs(int numberOfArgs, ...) {
	va_list args;
	va_start(args, numberOfArgs);
	PVOID* argsArr = va_arg(args, PVOID*);

	for (int i = 1; i < numberOfArgs; i++) {
		argsArr[i - 1] = va_arg(args, PVOID);
	}

	va_end(args);
}

MachineGunResult MachineGun(int numberOfArgs, PVOID* machineGunResult, std::wstring moduleName, std::string functionName, PVOID args[MAX_ARGS]) {
	MachineGunPkg machineGunPkg{};

	if (numberOfArgs > MAX_ARGS || numberOfArgs < 0)
		return INVALID_ARGS_NUMBER;

	// Getting the function.
	if (moduleName.empty())
		return MODULE_NOT_FOUND;
	HMODULE hModule = GetModuleHandle(moduleName.c_str());

	if (!hModule) {
		hModule = LoadLibrary(moduleName.c_str());

		if (!hModule)
			return MODULE_NOT_FOUND;
	}

	PVOID functionAddress = GetProcAddress(hModule, functionName.c_str());

	if (!functionAddress)
		return FUNCTION_NOT_FOUND;

	machineGunPkg.NumberOfArgs = reinterpret_cast<PVOID>(numberOfArgs);
	machineGunPkg.Function = functionAddress;

	// Loading the arguments.
	if (numberOfArgs > 0) {
		machineGunPkg.Arg1 = args[0];

		if (numberOfArgs > 1) {
			machineGunPkg.Arg2 = args[1];

			if (numberOfArgs > 2) {
				machineGunPkg.Arg3 = args[2];

				if (numberOfArgs > 3) {
					machineGunPkg.Arg4 = args[3];

					if (numberOfArgs > 4) {
						machineGunPkg.Arg5 = args[4];

						if (numberOfArgs > 5) {
							machineGunPkg.Arg6 = args[5];

							if (numberOfArgs > 6) {
								machineGunPkg.Arg7 = args[6];

								if (numberOfArgs > 7) {
									machineGunPkg.Arg8 = args[7];

									if (numberOfArgs > 8) {
										machineGunPkg.Arg9 = args[8];

										if (numberOfArgs > 9) {
											machineGunPkg.Arg10 = args[9];

											if (numberOfArgs > 10) {
												machineGunPkg.Arg11 = args[10];
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	*machineGunResult = MACHINEGUN_EXECUTE(&machineGunPkg);

Exit:
	return SUCCESS;
}

#endif
