#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/shm.h>
#include <sys/stat.h>
#include "parser.h"
#include <time.h>
#include <pthread.h>


typedef struct arg_struct {
    int *row;
    int *column;
    int size;
    int element_row;
    int element_col;
}Args;

Matrix* matrix1, *matrix2, *matrix3;

int calc_element(int* row, int* column, int size){
	int i = 0, element = 0;
	
	for(i = 0; i < size; i++)
		element += row[i] * column[i];

	return element;
}

void worker(void *arg){

	int i;
	int k = (int) arg;
	printf("Processo %d linhas : ", k);
	
	//TODO VER POR QUE TÁ ERRADO
	for(i=k;i<matrix1->row;i+=k){
		printf("%d", i);
	}

	
}

int main(int argc, const char *argv[]){

	int nroThreads,i,*k;
	pthread_t *threads;
	Args myArg;
	
	nroThreads = atoi(argv[1]);

	matrix1 = read_arquive("..//in1.txt");	
	matrix2 = read_arquive("..//in2.txt");
	
	threads = (pthread_t *) malloc(nroThreads * sizeof(pthread_t));
	
	sleep(5);
	if(matrix1->column != matrix2->row){
		printf("Dimensões de matrizes imcompatíveis para multiplicação\n");		
		exit(0);
	}
	
	
	// numero de processos maior que qts de elementos
	if(matrix1->row < nroThreads)
		nroThreads = matrix1->row ;	
	
	matrix3 = init_matrix(matrix1->row, matrix2->column);
	unsigned long s_time = clock();
	for(i=0;i<nroThreads;i++){
			pthread_create(&threads[i], NULL, worker, (void *)(i));
	}
	
	
	for (i = 0; i < nroThreads; i++) 
    	pthread_join(threads[i], NULL);
  	
  	unsigned long e_time = clock();
  	
  	 float diff = (((float)e_time - (float)s_time) / CLOCKS_PER_SEC) * 1000;   
 	 printf("TEMPO %f \n", diff ); 
	
	return 0;		
}
