	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15, 4	sdk_version 10, 15, 4
	.globl	_cowsum                 ## -- Begin function cowsum
	.p2align	4, 0x90
_cowsum:                                ## @cowsum
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	testl	%esi, %esi
	jle	LBB0_10
## %bb.1:
	testl	%edx, %edx
	jle	LBB0_10
## %bb.2:
	movl	%edx, %edx
	movl	%esi, %eax
	movl	%edx, %ecx
	andl	$7, %ecx
	movq	%rcx, %r8
	subq	%rdx, %r8
	leaq	-1(%rdx), %rsi
	xorl	%edi, %edi
	cmpq	$7, %rsi
	jb	LBB0_6
	jmp	LBB0_4
	.p2align	4, 0x90
LBB0_9:                                 ##   in Loop: Header=BB0_6 Depth=1
	incq	%rdi
	cmpq	%rax, %rdi
	je	LBB0_10
## %bb.3:                               ##   in Loop: Header=BB0_6 Depth=1
	cmpq	$7, %rsi
	jb	LBB0_6
LBB0_4:
	movq	%r8, %rdx
	.p2align	4, 0x90
LBB0_5:                                 ## =>This Inner Loop Header: Depth=1
	addq	$8, %rdx
	jne	LBB0_5
LBB0_6:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_8 Depth 2
	testq	%rcx, %rcx
	je	LBB0_9
## %bb.7:                               ##   in Loop: Header=BB0_6 Depth=1
	movq	%rcx, %rdx
	.p2align	4, 0x90
LBB0_8:                                 ##   Parent Loop BB0_6 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	decq	%rdx
	jne	LBB0_8
	jmp	LBB0_9
LBB0_10:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
