MACHINEGUN_EXECUTE proto

.data
arg_struct STRUCT
	numbofargs DQ 1
	function DQ 1
	arg1 DQ 1
	arg2 DQ 1
	arg3 DQ 1
	arg4 DQ 1
	arg5 DQ 1
	arg6 DQ 1
	arg7 DQ 1
	arg8 DQ 1
	arg9 DQ 1
	arg10 DQ 1
	arg11 DQ 1
arg_struct ENDS

.code

MACHINEGUN_EXECUTE proc
	mov rbx, rcx
	cmp [rbx].arg_struct.numbofargs, 1
	jl _EXECUTE
	mov rcx, [rbx].arg_struct.arg1

	cmp [rbx].arg_struct.numbofargs, 2
	jl _EXECUTE
	mov rdx, [rbx].arg_struct.arg2

	cmp [rbx].arg_struct.numbofargs, 3
	jl _EXECUTE
	mov r8, [rbx].arg_struct.arg3

	cmp [rbx].arg_struct.numbofargs, 4
	jl _EXECUTE
	mov r9, [rbx].arg_struct.arg4

	cmp [rbx].arg_struct.numbofargs, 5
	jl _EXECUTE
	mov rax, [rbx].arg_struct.arg5
	mov [rsp + 28h], rax

	cmp [rbx].arg_struct.numbofargs, 6
	jl _EXECUTE
	mov rax, [rbx].arg_struct.arg6
	mov [rsp + 30h], rax

	cmp [rbx].arg_struct.numbofargs, 7
	jl _EXECUTE
	mov rax, [rbx].arg_struct.arg7
	mov [rsp + 38h], rax

	cmp [rbx].arg_struct.numbofargs, 8
	jl _EXECUTE
	mov rax, [rbx].arg_struct.arg8
	mov [rsp + 40h], rax

	cmp [rbx].arg_struct.numbofargs, 9
	jl _EXECUTE
	mov rax, [rbx].arg_struct.arg9
	mov [rsp + 48h], rax

	cmp [rbx].arg_struct.numbofargs, 10
	jl _EXECUTE
	mov rax, [rbx].arg_struct.arg10
	mov [rsp + 50h], rax

	cmp [rbx].arg_struct.numbofargs, 11
	jl _EXECUTE
	mov rax, [rbx].arg_struct.arg11
	mov [rsp + 58h], rax

	_EXECUTE:
	jmp [rbx].arg_struct.function

MACHINEGUN_EXECUTE endp

end