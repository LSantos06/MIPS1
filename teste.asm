.data

w_n:	.word -64
w_p:	.word 64

.text
	la $s0, w_n
	la $s1, w_p
	
	lw $t0, 0($s0)
	lw $t1, 0($s1)
	
	lh $t2, 0($s0)
	lhu $t3, 0($s0)
	lh $t4, 0($s1)
	lhu $t5, 0($s1)
	
	lb $t6, 0($s0)
	lbu $t7, 0($s0)
	lb $t8, 0($s1)
	lbu $t9, 0($s1)
	
	# Termino do programa
	addi $v0, $zero, 10 # Codigo para terminar o programa = 10
	syscall 
