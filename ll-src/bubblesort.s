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
	movq	n@GOTPCREL(%rip), %rax
	movq	$99, (%rax)
	movq	j@GOTPCREL(%rip), %r12
	movq	$0, (%r12)
	movq	A@GOTPCREL(%rip), %r15
	leaq	literal(%rip), %rbx
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_2:                                # %for_body
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	(%r12), %rax
	movl	$100, %ecx
	subq	%rax, %rcx
	movq	%rcx, (%r15,%rax,8)
	movq	(%r12), %rax
	movq	(%r15,%rax,8), %rsi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	printf@PLT
	incq	(%r12)
.LBB0_1:                                # %for_pre
                                        # =>This Inner Loop Header: Depth=1
	movq	(%r12), %rax
	movq	n@GOTPCREL(%rip), %rcx
	cmpq	(%rcx), %rax
	jle	.LBB0_2
# BB#3:                                 # %for_post
	movq	i@GOTPCREL(%rip), %r14
	movq	$0, (%r14)
	movq	t@GOTPCREL(%rip), %r13
	leaq	literal.6(%rip), %rbx
	leaq	literal.5(%rip), %rbp
	jmp	.LBB0_4
	.p2align	4, 0x90
.LBB0_14:                               # %for_post24
                                        #   in Loop: Header=BB0_4 Depth=1
	incq	(%r14)
.LBB0_4:                                # %for_pre14
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_6 Depth 2
	movq	(%r14), %rax
	movq	n@GOTPCREL(%rip), %rcx
	cmpq	(%rcx), %rax
	jg	.LBB0_10
# BB#5:                                 # %for_body15
                                        #   in Loop: Header=BB0_4 Depth=1
	movq	(%r14), %rax
	movq	%rax, (%r12)
	jmp	.LBB0_6
	.p2align	4, 0x90
.LBB0_9:                                # %merge_block
                                        #   in Loop: Header=BB0_6 Depth=2
	xorl	%eax, %eax
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	callq	printf@PLT
	incq	(%r12)
.LBB0_6:                                # %for_pre22
                                        #   Parent Loop BB0_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%r12), %rax
	movq	n@GOTPCREL(%rip), %rcx
	cmpq	(%rcx), %rax
	jg	.LBB0_14
# BB#7:                                 # %for_body23
                                        #   in Loop: Header=BB0_6 Depth=2
	movq	(%r14), %rsi
	movq	(%r12), %rdx
	movq	(%r15,%rsi,8), %r8
	movq	(%r15,%rdx,8), %r9
	xorl	%eax, %eax
	leaq	literal.2(%rip), %rdi
	leaq	literal.1(%rip), %rcx
	callq	printf@PLT
	movq	(%r12), %rax
	movq	(%r15,%rax,8), %rax
	movq	(%r14), %rcx
	cmpq	(%r15,%rcx,8), %rax
	jge	.LBB0_9
# BB#8:                                 # %if_block
                                        #   in Loop: Header=BB0_6 Depth=2
	movq	(%r12), %rax
	movq	(%r15,%rax,8), %rcx
	movq	%rcx, (%r13)
	movq	(%r14), %rcx
	movq	(%r15,%rcx,8), %rcx
	movq	%rcx, (%r15,%rax,8)
	movq	(%r13), %rax
	movq	(%r14), %rcx
	movq	%rax, (%r15,%rcx,8)
	xorl	%eax, %eax
	leaq	literal.4(%rip), %rdi
	leaq	literal.3(%rip), %rsi
	callq	printf@PLT
	jmp	.LBB0_9
.LBB0_10:                               # %for_post16
	movq	$0, (%r12)
	leaq	literal.7(%rip), %rbx
	jmp	.LBB0_11
	.p2align	4, 0x90
.LBB0_12:                               # %for_body67
                                        #   in Loop: Header=BB0_11 Depth=1
	movq	(%r12), %rax
	movq	(%r15,%rax,8), %rsi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	printf@PLT
	incq	(%r12)
.LBB0_11:                               # %for_pre66
                                        # =>This Inner Loop Header: Depth=1
	movq	(%r12), %rax
	movq	n@GOTPCREL(%rip), %rcx
	cmpq	(%rcx), %rax
	jle	.LBB0_12
# BB#13:                                # %for_post68
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
	.type	t,@object               # @t
	.comm	t,8,8
	.type	j,@object               # @j
	.comm	j,8,8
	.type	i,@object               # @i
	.comm	i,8,8
	.type	n,@object               # @n
	.comm	n,8,8
	.type	literal,@object         # @literal
	.section	.rodata,"a",@progbits
literal:
	.asciz	"%d\n"
	.size	literal, 4

	.type	literal.1,@object       # @literal.1
literal.1:
	.asciz	"="
	.size	literal.1, 2

	.type	literal.2,@object       # @literal.2
literal.2:
	.asciz	"%d %d %s %d %d"
	.size	literal.2, 15

	.type	literal.3,@object       # @literal.3
literal.3:
	.asciz	" Swapping"
	.size	literal.3, 10

	.type	literal.4,@object       # @literal.4
literal.4:
	.asciz	"%s"
	.size	literal.4, 3

	.type	literal.5,@object       # @literal.5
literal.5:
	.zero	1
	.size	literal.5, 1

	.type	literal.6,@object       # @literal.6
literal.6:
	.asciz	"%s\n"
	.size	literal.6, 4

	.type	literal.7,@object       # @literal.7
literal.7:
	.asciz	"%d\n"
	.size	literal.7, 4


	.section	".note.GNU-stack","",@progbits
