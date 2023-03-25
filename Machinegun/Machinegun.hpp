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

MachineGunResult SetArgs(int numberOfArgs, ...) {
	va_list args;

	if (numberOfArgs > MAX_ARGS || numberOfArgs < 0)
		return INVALID_ARGS_NUMBER;
	numberOfArgs++;

	va_start(args, numberOfArgs);
	PVOID* argsArr = va_arg(args, PVOID*);

	for (int i = 1; i < numberOfArgs; i++) {
		argsArr[i - 1] = va_arg(args, PVOID);
	}

	va_end(args);
	return SUCCESS;
}

MachineGunResult MachineGun(int numberOfArgs, PVOID* machineGunResult, std::wstring moduleName, std::string functionName, PVOID args[MAX_ARGS]) {
	MachineGunPkg machineGunPkg{};
	PVOID* machineGunPkgArg = NULL;

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
	for (int i = 0; i < numberOfArgs; i++) {
		machineGunPkgArg = &((PVOID*)&machineGunPkg)[i + 2];
		*machineGunPkgArg = args[i];
	}

	*machineGunResult = MACHINEGUN_EXECUTE(&machineGunPkg);
	return SUCCESS;
}

#endif
