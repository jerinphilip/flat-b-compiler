	.text
	.file	"main"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %main_fn
	pushq	%rbp
.Lcfi0:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Lcfi1:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Lcfi2:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Lcfi3:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Lcfi4:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Lcfi5:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Lcfi6:
	.cfi_def_cfa_offset 64
.Lcfi7:
	.cfi_offset %rbx, -56
.Lcfi8:
	.cfi_offset %r12, -48
.Lcfi9:
	.cfi_offset %r13, -40
.Lcfi10:
	.cfi_offset %r14, -32
.Lcfi11:
	.cfi_offset %r15, -24
.Lcfi12:
	.cfi_offset %rbp, -16
	movq	n@GOTPCREL(%rip), %r12
	movq	$100, (%r12)
	movq	i@GOTPCREL(%rip), %rbx
	movq	$0, (%rbx)
	movq	A@GOTPCREL(%rip), %r13
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_2:                                # %for_body
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	(%rbx), %rax
	movq	%rax, (%r13,%rax,8)
	incq	(%rbx)
.LBB0_1:                                # %for_pre
                                        # =>This Inner Loop Header: Depth=1
	movq	(%r12), %rax
	decq	%rax
	cmpq	%rax, (%rbx)
	jle	.LBB0_2
# BB#3:                                 # %for_post
	movq	$0, (%rbx)
	leaq	literal.1(%rip), %r14
	leaq	literal(%rip), %r15
	jmp	.LBB0_4
	.p2align	4, 0x90
.LBB0_5:                                # %for_body11
                                        #   in Loop: Header=BB0_4 Depth=1
	movq	(%rbx), %rax
	movq	(%r13,%rax,8), %rsi
	xorl	%eax, %eax
	movq	%r14, %rdi
	movq	%r15, %rdx
	callq	printf@PLT
	incq	(%rbx)
.LBB0_4:                                # %for_pre10
                                        # =>This Inner Loop Header: Depth=1
	movq	(%r12), %rax
	decq	%rax
	cmpq	%rax, (%rbx)
	jle	.LBB0_5
# BB#6:                                 # %for_post12
	leaq	literal.3(%rip), %rdi
	leaq	literal.2(%rip), %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	movq	(%r12), %rax
	movq	%rax, %rcx
	shrq	$63, %rcx
	addq	%rax, %rcx
	sarq	%rcx
	movq	mid@GOTPCREL(%rip), %rax
	movq	%rcx, (%rax)
	movq	$0, (%rbx)
	movq	j@GOTPCREL(%rip), %rbp
	leaq	literal.4(%rip), %r15
	movq	t@GOTPCREL(%rip), %r14
	jmp	.LBB0_7
	.p2align	4, 0x90
.LBB0_8:                                # %for_body28
                                        #   in Loop: Header=BB0_7 Depth=1
	movq	(%r12), %rcx
	decq	%rcx
	movq	(%rbx), %rdx
	subq	%rdx, %rcx
	movq	%rcx, (%rbp)
	xorl	%eax, %eax
	leaq	literal.5(%rip), %rdi
	movq	%r15, %rsi
	callq	printf@PLT
	movq	(%rbx), %rax
	movq	(%r13,%rax,8), %rcx
	movq	%rcx, (%r14)
	movq	(%rbp), %rcx
	movq	(%r13,%rcx,8), %rcx
	movq	%rcx, (%r13,%rax,8)
	movq	(%r14), %rax
	movq	(%rbp), %rcx
	movq	%rax, (%r13,%rcx,8)
	incq	(%rbx)
.LBB0_7:                                # %for_pre27
                                        # =>This Inner Loop Header: Depth=1
	movq	mid@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	decq	%rax
	cmpq	%rax, (%rbx)
	jle	.LBB0_8
# BB#9:                                 # %for_post29
	movq	$0, (%rbx)
	leaq	literal.7(%rip), %r14
	leaq	literal.6(%rip), %r15
	jmp	.LBB0_10
	.p2align	4, 0x90
.LBB0_11:                               # %for_body57
                                        #   in Loop: Header=BB0_10 Depth=1
	movq	(%rbx), %rax
	movq	(%r13,%rax,8), %rsi
	xorl	%eax, %eax
	movq	%r14, %rdi
	movq	%r15, %rdx
	callq	printf@PLT
	incq	(%rbx)
.LBB0_10:                               # %for_pre56
                                        # =>This Inner Loop Header: Depth=1
	movq	(%r12), %rax
	decq	%rax
	cmpq	%rax, (%rbx)
	jle	.LBB0_11
# BB#12:                                # %for_post58
	leaq	literal.9(%rip), %rdi
	leaq	literal.8(%rip), %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	A,@object               # @A
	.comm	A,800,16
	.type	mid,@object             # @mid
	.comm	mid,8,8
	.type	n,@object               # @n
	.comm	n,8,8
	.type	j,@object               # @j
	.comm	j,8,8
	.type	i,@object               # @i
	.comm	i,8,8
	.type	t,@object               # @t
	.comm	t,8,8
	.type	literal,@object         # @literal
	.section	.rodata,"a",@progbits
literal:
	.zero	1
	.size	literal, 1

	.type	literal.1,@object       # @literal.1
literal.1:
	.asciz	"%d %s"
	.size	literal.1, 6

	.type	literal.2,@object       # @literal.2
literal.2:
	.zero	1
	.size	literal.2, 1

	.type	literal.3,@object       # @literal.3
literal.3:
	.asciz	"%s\n"
	.size	literal.3, 4

	.type	literal.4,@object       # @literal.4
literal.4:
	.asciz	"Swapping"
	.size	literal.4, 9

	.type	literal.5,@object       # @literal.5
literal.5:
	.asciz	"%s %d %d\n"
	.size	literal.5, 10

	.type	literal.6,@object       # @literal.6
literal.6:
	.zero	1
	.size	literal.6, 1

	.type	literal.7,@object       # @literal.7
literal.7:
	.asciz	"%d %s"
	.size	literal.7, 6

	.type	literal.8,@object       # @literal.8
literal.8:
	.zero	1
	.size	literal.8, 1

	.type	literal.9,@object       # @literal.9
literal.9:
	.asciz	"%s\n"
	.size	literal.9, 4


	.section	".note.GNU-stack","",@progbits
