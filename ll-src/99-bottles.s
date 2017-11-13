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
	movq	i@GOTPCREL(%rip), %rbx
	movq	$100, (%rbx)
	leaq	literal.1(%rip), %r14
	leaq	literal(%rip), %r15
	leaq	literal.3(%rip), %r12
	leaq	literal.2(%rip), %r13
	cmpq	$3, (%rbx)
	jl	.LBB0_3
	.p2align	4, 0x90
.LBB0_2:                                # %body
                                        # =>This Inner Loop Header: Depth=1
	movq	(%rbx), %rsi
	decq	%rsi
	movq	%rsi, (%rbx)
	xorl	%eax, %eax
	movq	%r14, %rdi
	movq	%r15, %rdx
	callq	printf@PLT
	xorl	%eax, %eax
	movq	%r12, %rdi
	movq	%r13, %rsi
	callq	printf@PLT
	cmpq	$3, (%rbx)
	jge	.LBB0_2
.LBB0_3:                                # %post
	movq	(%rbx), %rsi
	decq	%rsi
	movq	%rsi, (%rbx)
	leaq	literal.5(%rip), %rdi
	leaq	literal.4(%rip), %rdx
	xorl	%eax, %eax
	callq	printf@PLT
	leaq	literal.7(%rip), %rdi
	leaq	literal.6(%rip), %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	leaq	literal.9(%rip), %rdi
	leaq	literal.8(%rip), %rsi
	xorl	%eax, %eax
	callq	printf@PLT
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
	.type	i,@object               # @i
	.comm	i,8,8
	.type	literal,@object         # @literal
	.section	.rodata,"a",@progbits
	.p2align	4
literal:
	.asciz	"bottles of beer on the wall!"
	.size	literal, 29

	.type	literal.1,@object       # @literal.1
literal.1:
	.asciz	"%d %s\n"
	.size	literal.1, 7

	.type	literal.2,@object       # @literal.2
	.p2align	4
literal.2:
	.asciz	"Take one down, pass it around!"
	.size	literal.2, 31

	.type	literal.3,@object       # @literal.3
literal.3:
	.asciz	"%s\n"
	.size	literal.3, 4

	.type	literal.4,@object       # @literal.4
	.p2align	4
literal.4:
	.asciz	"bottles of beer on the wall!"
	.size	literal.4, 29

	.type	literal.5,@object       # @literal.5
literal.5:
	.asciz	"%d %s\n"
	.size	literal.5, 7

	.type	literal.6,@object       # @literal.6
	.p2align	4
literal.6:
	.asciz	"Take one down, pass it around!"
	.size	literal.6, 31

	.type	literal.7,@object       # @literal.7
literal.7:
	.asciz	"%s\n"
	.size	literal.7, 4

	.type	literal.8,@object       # @literal.8
	.p2align	4
literal.8:
	.asciz	"No more bottles of beer on the wall!"
	.size	literal.8, 37

	.type	literal.9,@object       # @literal.9
literal.9:
	.asciz	"%s\n"
	.size	literal.9, 4


	.section	".note.GNU-stack","",@progbits
