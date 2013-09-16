# Makefile para gerar executaveis de teste do programa
#Colocar no diretório home para funcionar compilação

# Caminhos Absolutos
parserInclude=../../sisop2-trab1/parser/

# comando para mover obj para  pasta bin: 'mv *.o ${bin}' 

teste_fila: 
	gcc -Wall -c -I $(includes) test_fila.c $(sources)fila.c  
	gcc -Wall fila.o test_fila.o -o teste
	mv *.o $(bin)



compile-execute:
	gcc -Wall -c -I $(parserInclude)  $(parserInclude)parser.c matrix_fork.c
	gcc parser.o matrix_fork.o -o matrix_fork
