.include "o/libc/nt/codegen.inc"
.imp	KernelBase,__imp_FindFirstFileW,FindFirstFileW,367

	.text.windows
FindFirstFile:
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	mov	__imp_FindFirstFileW(%rip),%rax
	jmp	__sysv2nt
	.endfn	FindFirstFile,globl
	.previous
