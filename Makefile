default: compilar

compilar:
		gcc -o simuladorMIPS_1.out simuladorMIPS_1.c

rodar:
		./simuladorMIPS_1.out

testes:
		gcc -o simuladorMIPS_1_testes.out simuladorMIPS_1_testes.c

testar:
		./simuladorMIPS_1_testes.out

limpar:
		rm *.out
