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
	 imull %eax,%eax           # eax <- n*n
	 xor %ecx, %ecx          # ecx = 0 usado para index
bucle:
	 cmpl %eax, %ecx
	 jge fi                  #index < n*n
	 movb (%esi), %bl
	 salb  $4, %bl           #bl = mata[i*n+j]*16
	 movb %bl, (%edi)        #matb[i*n+j]=(mata[i*n+j]*16)
	 inc %esi
	 inc %edi                #esi i edi + stride (1)
	 inc %ecx
	 jmp bucle
fi:

# El final de la rutina ya esta programado

	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
