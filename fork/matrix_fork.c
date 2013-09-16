#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/shm.h>
#include <sys/stat.h>
#include "parser.h"

/*******

Descrição: 	Multiplicação de matrizes utilizando fork
			Passar na linha de comando o numero de processos

*******/


// Calcula uma posição da matriz resultante
int calc_element(int* row, int* column, int size){
	int i = 0, element = 0;
	
	for(i = 0; i < size; i++)
		element += row[i] * column[i];

	return element;
}



int main(int argc, const char *argv[]){

    
	int processos = 0, i = 0;
	pid_t pid = 0;
	//int status;
	int segment_id = 0;	
	Matrix* matrix1 = NULL;
	Matrix* matrix2 = NULL;
	Matrix* matrix3 = NULL; // shared memory



// Verifica se foi passado o numero de processos a ser criado
	if (argc != 2) {
	   printf ("\n**************************************************\n\n");	
       printf ("Ops!! Informe um número inteiro, Ex: matrix_fork 2\n");
	   printf ("\n**************************************************\n\n");	
       exit(0);
    }      

    processos = atoi(argv[1]);
	matrix1 = read_arquive("..//in1.txt");	
	matrix2 = read_arquive("..//in2.txt");
	
	if(matrix1->column != matrix2->row){
		printf("Dimensões de matrizes imcompatíveis para muultiplicação\n");		
		exit(0);
	}

	// numero de processos maior que qts de elementos
	if(matrix1->row * matrix2->column < processos)
		processos = matrix1->row * matrix2->column;	
	

	// Alocar memoria do segmento

/*	
	segment_id = shmget(IPC_PRIVATE, sizeof(Matrix), S_IRUSR | S_IWUSR);	
	matrix3 = (Matrix*) shmat(segment_id, NULL, 0);
	init(matrix3, matrix1->row, matrix2->column);
	shmdt(matrix3);
	shmctl(segment_id, IPC_RMID, NULL);
	*/
	
	// Elementos de matrix resultante divido pelo processos
	int divider = matrix1->row / processos;
	int rest = matrix1->row % processos;
	int step = divider + rest;
	int k = 0, j = 0;
	

	// cria varios processos  
	
	

	for(i = 0; i < processos; i++){
		pid = fork();		
		if( pid == 0){// Processo filho
		  for(k; k < step; k++){				
			for(j = 0; j < matrix2->column; j++){
			
				int* linha = getRowMatrix(matrix1, k);
				int* col = getColumnMatrix(matrix2, j);
				int e = calc_element(linha, col, matrix1->column);
		
				/* detach the shared memory segment */    
				//matrix3 = (Matrix*) shmat(segment_id, NULL, 0);
					
				printf("calc:%d, num processo: %d\n",e, i);
				}
			}
			/* detach the shared memory segment */    
			//shmdt(matrix3);
	
			/* remove the shared memory segment */   
			//shmctl(segment_id, IPC_RMID, NULL);
			
			exit(0);
		}else{	// processo pai	
			k = step;		
			step += divider;			
			printf("Pai %d\n",pid);
		}
	}


	//waitpid(pid,0,0);	
	//wait(&status);
	//while (-1 == waitpid(-1, NULL, 0));
	for(i=0; i<processos; i++){
	    wait(NULL);
	    
	  }
	//printf("executing %d %d\n", pid, WEXITSTATUS(status));
	printf("executing parent\n");
	free(matrix1);
	free(matrix2);
	free(matrix3);

    
	return 0;
	  
}
