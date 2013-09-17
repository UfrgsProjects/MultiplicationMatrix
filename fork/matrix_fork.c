#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/shm.h>
#include <sys/stat.h>
#include "parser.h"
#include <time.h>

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
	int segment_id = 0;	
	Matrix* matrix1 = NULL;
	Matrix* matrix2 = NULL;
	Matrix* matrix3 = NULL; // shared memory
	int *matrix;
	int k = 0, j = 0;
	int divider = 0;	
	int rest = 0;
	int step = 0;
	time_t start, end;
	clock_t clock_start, clock_end;

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
		printf("Dimensões de matrizes imcompatíveis para multiplicação\n");		
		exit(0);
	}

	// numero de processos maior que qts de elementos
	if(matrix1->row < processos)
		processos = matrix1->row ;	
	
	matrix3 = init_matrix(matrix1->row, matrix2->column);

	// Alocar memoria do segmento
	segment_id = shmget(IPC_PRIVATE, sizeof(int) * matrix1->row * matrix2->column, S_IRUSR | S_IWUSR);	

	if(segment_id < 0){
		printf("Impossível de criar memoria compartilhada\n");
		exit(0);
	}	

	/* attach the shared memory segment */   	
	matrix = (int *)shmat(segment_id, 0, 0);
	
	// Elementos de matrix resultante divido pelo processos
	divider = matrix1->row / processos;
	rest = matrix1->row % processos;
	step = divider + rest;
	
	
	unsigned long s_time = clock();
	// cria varios processos  
	
	for(i = 0; i < processos; i++){
		pid = fork();	
		
		if( pid == 0){// Processo filho
		 
		  for(k; k < step; k++){				
			for(j = 0; j < matrix2->column; j++){
			  int* linha = getRowMatrix(matrix1, k);
			  int* col = getColumnMatrix(matrix2, j);
			  int e = calc_element(linha, col, matrix1->column);
			  matrix[ k*matrix2->column + j ] = e;				  
			 }
		  }
		
		 exit(1);
		}else{	// processo pai	
			k = step;		
			step += divider;			
		}
	}

	// Espera processos filhos acabar
	for(i=0; i<processos; i++){
	    wait(NULL);
	}
	unsigned long e_time = clock();
	 
	 /* TODO COUNT THE TIME SPENT */

 	//float diff = (((float)e_time - (float)s_time) / CLOCKS_PER_SEC) * 1000;   
 	//printf("TEMPO %f \n", diff ); 
	
	// Passando para o formato da estrutura matrix
	for (k = 0; k < matrix1->row; k++){
      for (j = 0; j < matrix2->column; j++){
			printf("%d ",matrix[k*matrix2->column + j]); 
			matrix3->value[k][j] = matrix[k*matrix2->column + j];
    	}
	  printf("\n");	
	 }

	/*

		Não consegui escrever a saida do no arquivo de texto unica coisa que falta
*/
	
	write_arquive("..//out.txt", matrix3);		

	/* detach the shared memory segment */    
	shmdt((void*)matrix);
	 /* remove the shared memory segment */   
	shmctl(segment_id, IPC_RMID, NULL);

	free(matrix1);
	free(matrix2);
	free(matrix3);

	return 0;
}
