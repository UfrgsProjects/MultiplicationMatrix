#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "parser.h"
#include <time.h>
#include <pthread.h>
#include <string.h>

Matrix* matrix1, *matrix2, *matrix3;
int nroThreads;

int calc_element(int* row, int* column, int size){
	int i = 0, element = 0;
	
	for(i = 0; i < size; i++)
		element += row[i] * column[i];

	return element;
}

void worker(void *arg){

	int i,j;
	int k = (int) arg;
	int *row, *col;
	
	for(i=k;i<matrix1->row;i+=nroThreads){
	row = getRowMatrix(matrix1, i);
		for(j=0;j<matrix2->column;j++){
		col = getColumnMatrix(matrix2,j);
		matrix3->value[i][j] = calc_element(row,col,matrix1->row);
		//printf("[%d][%d] %d", i,j, matrix3->value[i][j]);
		}
	}
	
}

int main(int argc, const char *argv[]){

	int i,*k;
	pthread_t *threads;
	FILE* file_tempo = fopen("tempo.txt","w"); 
	//Cuidado, essa medida de tempo não é portável!
	struct timespec ts,tf;
	
	nroThreads = atoi(argv[1]);
	matrix1 = read_arquive("..//in1.txt");	
	matrix2 = read_arquive("..//in2.txt");
	
	threads = (pthread_t *) malloc(nroThreads * sizeof(pthread_t));
	k = (int *) malloc(nroThreads * sizeof(int));
	if(matrix1->column != matrix2->row){
		printf("Dimensões de matrizes imcompatíveis para multiplicação\n");		
		exit(0);
	}
	
	
	// numero de processos maior que qts de elementos
	if(matrix1->row < nroThreads)
		nroThreads = matrix1->row ;	


	matrix3 = init_matrix(matrix1->row, matrix2->column);
	
	//matrix1->row = 10;	
	
	clock_gettime(CLOCK_MONOTONIC, &ts);
	for(i=0;i<nroThreads;i++){
		k[i] = i;
		//printf("nro thread %d \n", k[i]);
	        pthread_create(&threads[i], NULL, worker, (void *)(i));
	}
	
	for (i = 0; i < nroThreads; i++) 
    	  pthread_join(threads[i], NULL);
  	
  	clock_gettime(CLOCK_MONOTONIC, &tf);

	 printf("TEMPO s: %f  ms: %f \n", (double)(tf.tv_sec - ts.tv_sec) , ( ((double) (tf.tv_nsec - ts.tv_nsec)) / 1000)); 
	 fprintf(file_tempo,"%f \n",(((double) (tf.tv_nsec - ts.tv_nsec)) / 1000));
	 write_arquive("..//out.txt",matrix3);
	return 0;		
}
