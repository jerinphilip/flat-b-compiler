	.text
	.file	"main"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %main_fn
	pushq	%r15
.Lcfi0:
	.cfi_def_cfa_offset 16
	pushq	%r14
.Lcfi1:
	.cfi_def_cfa_offset 24
	pushq	%r13
.Lcfi2:
	.cfi_def_cfa_offset 32
	pushq	%r12
.Lcfi3:
	.cfi_def_cfa_offset 40
	pushq	%rbx
.Lcfi4:
	.cfi_def_cfa_offset 48
.Lcfi5:
	.cfi_offset %rbx, -48
.Lcfi6:
	.cfi_offset %r12, -40
.Lcfi7:
	.cfi_offset %r13, -32
.Lcfi8:
	.cfi_offset %r14, -24
.Lcfi9:
	.cfi_offset %r15, -16
	movq	n@GOTPCREL(%rip), %r15
	movq	$12, (%r15)
	movq	a@GOTPCREL(%rip), %r12
	movq	$0, (%r12)
	movq	b@GOTPCREL(%rip), %rbx
	movq	$1, (%rbx)
	movq	t@GOTPCREL(%rip), %r13
	leaq	literal(%rip), %r14
	cmpq	$0, (%r15)
	jle	.LBB0_3
	.p2align	4, 0x90
.LBB0_2:                                # %body
                                        # =>This Inner Loop Header: Depth=1
	movq	(%r12), %rdx
	movq	%rdx, (%r13)
	movq	(%rbx), %rsi
	movq	%rsi, (%r12)
	addq	%rsi, %rdx
	movq	%rdx, (%rbx)
	xorl	%eax, %eax
	movq	%r14, %rdi
	callq	printf@PLT
	decq	(%r15)
	cmpq	$0, (%r15)
	jg	.LBB0_2
.LBB0_3:                                # %post
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	b,@object               # @b
	.comm	b,8,8
	.type	a,@object               # @a
	.comm	a,8,8
	.type	n,@object               # @n
	.comm	n,8,8
	.type	t,@object               # @t
	.comm	t,8,8
	.type	literal,@object         # @literal
	.section	.rodata,"a",@progbits
literal:
	.asciz	"%d %d\n"
	.size	literal, 7


	.section	".note.GNU-stack","",@progbits
