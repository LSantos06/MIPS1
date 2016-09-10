.data

x:	.word -2048
y:	.word 64

.text
	la $s0, x
	la $s1, y
	
	# Multiplos de 4
	lh $t1, 2($s0)
	lhu $t2, 0($s0)
	
	lb $t3, 0($s1)
	lbu $t4, 0($s1)
	
	# Multiplos de 2
	#sb $s0, 8($t5)
	#sh $t2, 0($t4)

	# Sem restricao
	#lb $t1, 4($t1)
	
	# Termino do programa
	addi $v0, $zero, 10 # Codigo para terminar o programa = 10
	syscall 
