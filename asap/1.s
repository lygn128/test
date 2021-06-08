	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15, 4	sdk_version 10, 15, 4
	.globl	_sum                    ## -- Begin function sum
	.p2align	4, 0x90
_sum:                                   ## @sum
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	addl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	_accum(%rip), %eax
	movl	%eax, _accum(%rip)
	movl	-12(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_sp_init                ## -- Begin function sp_init
	.p2align	4, 0x90
_sp_init:                               ## @sp_init
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	%rax, 16(%rcx)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_rowsum                 ## -- Begin function rowsum
	.p2align	4, 0x90
_rowsum:                                ## @rowsum
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movl	%esi, -20(%rbp)
	movl	%edx, -24(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -32(%rbp)
LBB2_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB2_3 Depth 2
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB2_8
## %bb.2:                               ##   in Loop: Header=BB2_1 Depth=1
	movl	$0, -36(%rbp)
LBB2_3:                                 ##   Parent Loop BB2_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	-36(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jge	LBB2_6
## %bb.4:                               ##   in Loop: Header=BB2_3 Depth=2
	movq	-16(%rbp), %rax
	movslq	-32(%rbp), %rcx
	imulq	$400, %rcx, %rcx        ## imm = 0x190
	addq	%rcx, %rax
	movslq	-36(%rbp), %rcx
	movl	(%rax,%rcx,4), %edx
	addl	-28(%rbp), %edx
	movl	%edx, -28(%rbp)
## %bb.5:                               ##   in Loop: Header=BB2_3 Depth=2
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB2_3
LBB2_6:                                 ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_7
LBB2_7:                                 ##   in Loop: Header=BB2_1 Depth=1
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
	jmp	LBB2_1
LBB2_8:
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
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
	movq	%rdi, -16(%rbp)
	movl	%esi, -20(%rbp)
	movl	%edx, -24(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -32(%rbp)
LBB3_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB3_3 Depth 2
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB3_8
## %bb.2:                               ##   in Loop: Header=BB3_1 Depth=1
	movl	$0, -36(%rbp)
LBB3_3:                                 ##   Parent Loop BB3_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	-36(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jge	LBB3_6
## %bb.4:                               ##   in Loop: Header=BB3_3 Depth=2
	movq	-16(%rbp), %rax
	movslq	-36(%rbp), %rcx
	imulq	$400, %rcx, %rcx        ## imm = 0x190
	addq	%rcx, %rax
	movslq	-32(%rbp), %rcx
	movl	(%rax,%rcx,4), %edx
	addl	-28(%rbp), %edx
	movl	%edx, -28(%rbp)
## %bb.5:                               ##   in Loop: Header=BB3_3 Depth=2
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	LBB3_3
LBB3_6:                                 ##   in Loop: Header=BB3_1 Depth=1
	jmp	LBB3_7
LBB3_7:                                 ##   in Loop: Header=BB3_1 Depth=1
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
	jmp	LBB3_1
LBB3_8:
	movl	-4(%rbp), %eax
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
	movl	$4000032, %eax          ## imm = 0x3D0920
	callq	____chkstk_darwin
	subq	%rax, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -4000020(%rbp)
	movl	$0, -4000024(%rbp)
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$10000, -4000024(%rbp)  ## imm = 0x2710
	jge	LBB4_4
## %bb.2:                               ##   in Loop: Header=BB4_1 Depth=1
	leaq	-4000016(%rbp), %rdi
	movl	$10000, %esi            ## imm = 0x2710
	movl	$100, %edx
	callq	_cowsum
## %bb.3:                               ##   in Loop: Header=BB4_1 Depth=1
	movl	-4000024(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -4000024(%rbp)
	jmp	LBB4_1
LBB4_4:
	movl	-4000020(%rbp), %eax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	movl	%eax, -4000028(%rbp)    ## 4-byte Spill
	jne	LBB4_6
## %bb.5:
	movl	-4000028(%rbp), %eax    ## 4-byte Reload
	addq	$4000032, %rsp          ## imm = 0x3D0920
	popq	%rbp
	retq
LBB4_6:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_accum                  ## @accum
.zerofill __DATA,__common,_accum,4,2

.subsections_via_symbols
