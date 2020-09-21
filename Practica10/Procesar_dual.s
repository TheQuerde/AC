.text
	.align 4
	.globl procesar
	.type	procesar, @function
procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo

	movl 8(%ebp), %esi      # esi <- mata
	movl 12(%ebp), %edi     # edi <- matb
	movl 16(%ebp), %eax
	imull %eax, %eax           # eax <- n*n
	xor %ecx, %ecx          # ecx = 0 usado para index
bucle:
	cmpl %eax, %ecx
	jge fi                  #index < n*n
  movl $65520, %ebx
  and %esi, %ebx
  cmpl $0,%ebx
  je aligned_1
unaligned_1:
	movdqu (%esi), %xmm0
  jmp fi_unaligned_1
aligned_1:
  movdqa (%esi), %xmm0
fi_unaligned_1:
	psllq  $4, %xmm0
  movl $65520, %ebx
  and %edi, %ebx
  cmpl $0,%ebx
  je aligned_2
unaligned_2:
	movdqu %xmm0, (%edi)
  jmp fi_unaligned_2
aligned_2:
  movdqa %xmm0, (%edi)
fi_unaligned_2:
	addl $16, %esi
	addl $16, %edi
	addl $16, %ecx
	jmp bucle
fi:

# El final de la rutina ya esta programado

	emms	# Instruccion necesaria si os equivocais y usais MMX
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
