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
	movdqu (%esi), %xmm0
	psllq  $4, %xmm0
	movdqu %xmm0, (%edi)
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
