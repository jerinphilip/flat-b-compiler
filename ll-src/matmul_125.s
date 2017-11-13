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
	movq	n@GOTPCREL(%rip), %r14
	movq	$124, (%r14)
	movq	i@GOTPCREL(%rip), %r8
	movq	$0, (%r8)
	movq	j@GOTPCREL(%rip), %r15
	movq	a@GOTPCREL(%rip), %r9
	movq	A@GOTPCREL(%rip), %r12
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_42:                               # %for_post7
                                        #   in Loop: Header=BB0_1 Depth=1
	incq	(%r8)
.LBB0_1:                                # %for_pre
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	movq	(%r8), %rax
	cmpq	(%r14), %rax
	jg	.LBB0_8
# BB#2:                                 # %for_body
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	$0, (%r15)
	jmp	.LBB0_3
	.p2align	4, 0x90
.LBB0_5:                                # %if_block
                                        #   in Loop: Header=BB0_3 Depth=2
	movq	(%r8), %rax
	imulq	(%r14), %rax
	addq	(%r15), %rax
	movq	%rax, (%r9)
	movq	$1, (%r12,%rax,8)
	incq	(%r15)
.LBB0_3:                                # %for_pre5
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%r15), %rax
	cmpq	(%r14), %rax
	jg	.LBB0_42
# BB#4:                                 # %for_body6
                                        #   in Loop: Header=BB0_3 Depth=2
	movq	(%r8), %rax
	cmpq	(%r15), %rax
	je	.LBB0_5
# BB#7:                                 # %else_block
                                        #   in Loop: Header=BB0_3 Depth=2
	movq	(%r8), %rax
	imulq	(%r14), %rax
	addq	(%r15), %rax
	movq	%rax, (%r9)
	movq	$0, (%r12,%rax,8)
	incq	(%r15)
	jmp	.LBB0_3
.LBB0_8:                                # %for_post
	movq	$0, (%r8)
	movq	B@GOTPCREL(%rip), %r13
	jmp	.LBB0_9
	.p2align	4, 0x90
.LBB0_43:                               # %for_post46
                                        #   in Loop: Header=BB0_9 Depth=1
	incq	(%r8)
.LBB0_9:                                # %for_pre36
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_11 Depth 2
	movq	(%r8), %rax
	cmpq	(%r14), %rax
	jg	.LBB0_16
# BB#10:                                # %for_body37
                                        #   in Loop: Header=BB0_9 Depth=1
	movq	$0, (%r15)
	jmp	.LBB0_11
	.p2align	4, 0x90
.LBB0_13:                               # %if_block57
                                        #   in Loop: Header=BB0_11 Depth=2
	movq	(%r8), %rax
	imulq	(%r14), %rax
	addq	(%r15), %rax
	movq	%rax, (%r9)
	movq	$1, (%r13,%rax,8)
	incq	(%r15)
.LBB0_11:                               # %for_pre44
                                        #   Parent Loop BB0_9 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%r15), %rax
	cmpq	(%r14), %rax
	jg	.LBB0_43
# BB#12:                                # %for_body45
                                        #   in Loop: Header=BB0_11 Depth=2
	movq	(%r8), %rax
	cmpq	(%r15), %rax
	je	.LBB0_13
# BB#15:                                # %else_block66
                                        #   in Loop: Header=BB0_11 Depth=2
	movq	(%r8), %rax
	imulq	(%r14), %rax
	addq	(%r15), %rax
	movq	%rax, (%r9)
	movq	$0, (%r13,%rax,8)
	incq	(%r15)
	jmp	.LBB0_11
.LBB0_16:                               # %for_post38
	movq	$0, (%r8)
	movq	k@GOTPCREL(%rip), %rax
	movq	b@GOTPCREL(%rip), %r10
	movq	c@GOTPCREL(%rip), %rdx
	movq	C@GOTPCREL(%rip), %rcx
	jmp	.LBB0_17
	.p2align	4, 0x90
.LBB0_44:                               # %for_post88
                                        #   in Loop: Header=BB0_17 Depth=1
	incq	(%r8)
.LBB0_17:                               # %for_pre78
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_19 Depth 2
                                        #       Child Loop BB0_21 Depth 3
	movq	(%r8), %rsi
	cmpq	(%r14), %rsi
	jg	.LBB0_24
# BB#18:                                # %for_body79
                                        #   in Loop: Header=BB0_17 Depth=1
	movq	$0, (%r15)
	jmp	.LBB0_19
	.p2align	4, 0x90
.LBB0_23:                               # %for_post96
                                        #   in Loop: Header=BB0_19 Depth=2
	incq	(%r15)
.LBB0_19:                               # %for_pre86
                                        #   Parent Loop BB0_17 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB0_21 Depth 3
	movq	(%r15), %rsi
	cmpq	(%r14), %rsi
	jg	.LBB0_44
# BB#20:                                # %for_body87
                                        #   in Loop: Header=BB0_19 Depth=2
	movq	$0, (%rax)
	jmp	.LBB0_21
	.p2align	4, 0x90
.LBB0_22:                               # %for_body95
                                        #   in Loop: Header=BB0_21 Depth=3
	movq	(%r14), %rsi
	movq	(%r8), %rdi
	imulq	%rsi, %rdi
	movq	(%rax), %rbp
	leaq	(%rdi,%rbp), %rbx
	movq	%rbx, (%r9)
	imulq	%rsi, %rbp
	movq	(%r15), %rsi
	addq	%rsi, %rbp
	movq	%rbp, (%r10)
	addq	%rsi, %rdi
	movq	%rdi, (%rdx)
	movq	(%r12,%rbx,8), %rsi
	imulq	(%r13,%rbp,8), %rsi
	addq	%rsi, (%rcx,%rdi,8)
	incq	(%rax)
.LBB0_21:                               # %for_pre94
                                        #   Parent Loop BB0_17 Depth=1
                                        #     Parent Loop BB0_19 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movq	(%rax), %rsi
	cmpq	(%r14), %rsi
	jle	.LBB0_22
	jmp	.LBB0_23
.LBB0_24:                               # %for_post80
	movq	%r9, %rbp
	leaq	literal.1(%rip), %rdi
	leaq	literal(%rip), %rsi
	xorl	%eax, %eax
	movq	%r8, %rbx
	callq	printf@PLT
	movq	%rbx, %rcx
	movq	$0, (%rcx)
	jmp	.LBB0_25
	.p2align	4, 0x90
.LBB0_29:                               # %for_post146
                                        #   in Loop: Header=BB0_25 Depth=1
	xorl	%eax, %eax
	leaq	literal.5(%rip), %rdi
	leaq	literal.4(%rip), %rsi
	callq	printf@PLT
	movq	%rbx, %rcx
	incq	(%rcx)
.LBB0_25:                               # %for_pre136
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_27 Depth 2
	movq	(%rcx), %rax
	cmpq	(%r14), %rax
	movq	%rbp, %rdx
	jg	.LBB0_30
# BB#26:                                # %for_body137
                                        #   in Loop: Header=BB0_25 Depth=1
	movq	$0, (%r15)
	jmp	.LBB0_27
	.p2align	4, 0x90
.LBB0_28:                               # %for_body145
                                        #   in Loop: Header=BB0_27 Depth=2
	movq	(%rcx), %rax
	imulq	(%r14), %rax
	addq	(%r15), %rax
	movq	%rax, (%rdx)
	movq	(%r12,%rax,8), %rsi
	xorl	%eax, %eax
	leaq	literal.3(%rip), %rdi
	leaq	literal.2(%rip), %rdx
	callq	printf@PLT
	movq	%rbp, %rdx
	movq	%rbx, %rcx
	incq	(%r15)
.LBB0_27:                               # %for_pre144
                                        #   Parent Loop BB0_25 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%r15), %rax
	cmpq	(%r14), %rax
	jle	.LBB0_28
	jmp	.LBB0_29
.LBB0_30:                               # %for_post138
	leaq	literal.7(%rip), %rdi
	leaq	literal.6(%rip), %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	leaq	literal.9(%rip), %rdi
	leaq	literal.8(%rip), %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	movq	%rbx, %rcx
	movq	$0, (%rcx)
	leaq	literal.11(%rip), %r12
	jmp	.LBB0_31
	.p2align	4, 0x90
.LBB0_35:                               # %for_post178
                                        #   in Loop: Header=BB0_31 Depth=1
	xorl	%eax, %eax
	leaq	literal.13(%rip), %rdi
	leaq	literal.12(%rip), %rsi
	callq	printf@PLT
	movq	%rbx, %rcx
	incq	(%rcx)
.LBB0_31:                               # %for_pre168
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_33 Depth 2
	movq	(%rcx), %rax
	cmpq	(%r14), %rax
	jg	.LBB0_36
# BB#32:                                # %for_body169
                                        #   in Loop: Header=BB0_31 Depth=1
	movq	$0, (%r15)
	jmp	.LBB0_33
	.p2align	4, 0x90
.LBB0_34:                               # %for_body177
                                        #   in Loop: Header=BB0_33 Depth=2
	movq	(%rcx), %rax
	imulq	(%r14), %rax
	addq	(%r15), %rax
	movq	%rax, (%rdx)
	movq	(%r13,%rax,8), %rsi
	xorl	%eax, %eax
	movq	%r12, %rdi
	leaq	literal.10(%rip), %rdx
	callq	printf@PLT
	movq	%rbx, %rcx
	incq	(%r15)
.LBB0_33:                               # %for_pre176
                                        #   Parent Loop BB0_31 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%r15), %rax
	cmpq	(%r14), %rax
	movq	%rbp, %rdx
	jle	.LBB0_34
	jmp	.LBB0_35
.LBB0_36:                               # %for_post170
	leaq	literal.15(%rip), %rdi
	leaq	literal.14(%rip), %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	leaq	literal.17(%rip), %rdi
	leaq	literal.16(%rip), %rsi
	xorl	%eax, %eax
	callq	printf@PLT
	movq	%rbx, %rcx
	movq	$0, (%rcx)
	leaq	literal.19(%rip), %r12
	leaq	literal.18(%rip), %r13
	jmp	.LBB0_37
	.p2align	4, 0x90
.LBB0_41:                               # %for_post210
                                        #   in Loop: Header=BB0_37 Depth=1
	xorl	%eax, %eax
	leaq	literal.21(%rip), %rdi
	leaq	literal.20(%rip), %rsi
	callq	printf@PLT
	movq	%rbx, %rcx
	incq	(%rcx)
.LBB0_37:                               # %for_pre200
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_39 Depth 2
	movq	(%rcx), %rax
	cmpq	(%r14), %rax
	jg	.LBB0_45
# BB#38:                                # %for_body201
                                        #   in Loop: Header=BB0_37 Depth=1
	movq	$0, (%r15)
	jmp	.LBB0_39
	.p2align	4, 0x90
.LBB0_40:                               # %for_body209
                                        #   in Loop: Header=BB0_39 Depth=2
	movq	(%rcx), %rax
	imulq	(%r14), %rax
	addq	(%r15), %rax
	movq	%rax, (%rdx)
	movq	(%rsi,%rax,8), %rsi
	xorl	%eax, %eax
	movq	%r12, %rdi
	movq	%r13, %rdx
	callq	printf@PLT
	movq	%rbx, %rcx
	incq	(%r15)
.LBB0_39:                               # %for_pre208
                                        #   Parent Loop BB0_37 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%r15), %rax
	cmpq	(%r14), %rax
	movq	%rbp, %rdx
	movq	C@GOTPCREL(%rip), %rsi
	jle	.LBB0_40
	jmp	.LBB0_41
.LBB0_45:                               # %for_post202
	leaq	literal.23(%rip), %rdi
	leaq	literal.22(%rip), %rsi
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
	.type	C,@object               # @C
	.comm	C,125000,16
	.type	B,@object               # @B
	.comm	B,125000,16
	.type	A,@object               # @A
	.comm	A,125000,16
	.type	n,@object               # @n
	.comm	n,8,8
	.type	k,@object               # @k
	.comm	k,8,8
	.type	j,@object               # @j
	.comm	j,8,8
	.type	i,@object               # @i
	.comm	i,8,8
	.type	c,@object               # @c
	.comm	c,8,8
	.type	b,@object               # @b
	.comm	b,8,8
	.type	a,@object               # @a
	.comm	a,8,8
	.type	literal,@object         # @literal
	.section	.rodata,"a",@progbits
literal:
	.asciz	"A:"
	.size	literal, 3

	.type	literal.1,@object       # @literal.1
literal.1:
	.asciz	"%s\n"
	.size	literal.1, 4

	.type	literal.2,@object       # @literal.2
literal.2:
	.asciz	" "
	.size	literal.2, 2

	.type	literal.3,@object       # @literal.3
literal.3:
	.asciz	"%d %s"
	.size	literal.3, 6

	.type	literal.4,@object       # @literal.4
literal.4:
	.zero	1
	.size	literal.4, 1

	.type	literal.5,@object       # @literal.5
literal.5:
	.asciz	"%s\n"
	.size	literal.5, 4

	.type	literal.6,@object       # @literal.6
literal.6:
	.asciz	"---"
	.size	literal.6, 4

	.type	literal.7,@object       # @literal.7
literal.7:
	.asciz	"%s\n"
	.size	literal.7, 4

	.type	literal.8,@object       # @literal.8
literal.8:
	.asciz	"B:"
	.size	literal.8, 3

	.type	literal.9,@object       # @literal.9
literal.9:
	.asciz	"%s\n"
	.size	literal.9, 4

	.type	literal.10,@object      # @literal.10
literal.10:
	.asciz	" "
	.size	literal.10, 2

	.type	literal.11,@object      # @literal.11
literal.11:
	.asciz	"%d %s"
	.size	literal.11, 6

	.type	literal.12,@object      # @literal.12
literal.12:
	.zero	1
	.size	literal.12, 1

	.type	literal.13,@object      # @literal.13
literal.13:
	.asciz	"%s\n"
	.size	literal.13, 4

	.type	literal.14,@object      # @literal.14
literal.14:
	.asciz	"---"
	.size	literal.14, 4

	.type	literal.15,@object      # @literal.15
literal.15:
	.asciz	"%s\n"
	.size	literal.15, 4

	.type	literal.16,@object      # @literal.16
literal.16:
	.asciz	"AB = C:"
	.size	literal.16, 8

	.type	literal.17,@object      # @literal.17
literal.17:
	.asciz	"%s\n"
	.size	literal.17, 4

	.type	literal.18,@object      # @literal.18
literal.18:
	.asciz	" "
	.size	literal.18, 2

	.type	literal.19,@object      # @literal.19
literal.19:
	.asciz	"%d %s"
	.size	literal.19, 6

	.type	literal.20,@object      # @literal.20
literal.20:
	.zero	1
	.size	literal.20, 1

	.type	literal.21,@object      # @literal.21
literal.21:
	.asciz	"%s\n"
	.size	literal.21, 4

	.type	literal.22,@object      # @literal.22
literal.22:
	.asciz	"---"
	.size	literal.22, 4

	.type	literal.23,@object      # @literal.23
literal.23:
	.asciz	"%s\n"
	.size	literal.23, 4


	.section	".note.GNU-stack","",@progbits
