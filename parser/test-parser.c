#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


int main(){

	int i = 0, j = 0;
	Matrix* m1 = read_arquive("..//in1.txt");	

	printf("**Arquivo in1.txt\n");

	for(i = 0; i < m1->row; i++){
		for(j = 0; j < m1->column; j++){
			printf("\t%d ",m1->value[i][j]);
		}
		printf("\n");	
	}

	printf("**Arquivo in2.txt\n");

	Matrix* m2 = read_arquive("..//in2.txt");	

	for(i = 0; i < m2->row; i++){
		for(j = 0; j < m2->column; j++){
			printf("\t%d ",m2->value[i][j]);
		}
		printf("\n");	
	}

	printf("Matrix1 line2\n ");
	int* line = getRowMatrix(m1, 1);
	for(i = 0; i < m1->column; i++)
		printf("%d ",line[i]);	
	
	printf("\n");

	printf("Matrix2 column3\n ");
	int* col = getColumnMatrix(m2, 2);
	for(i = 0; i < m2->row; i++)
		printf("%d ",col[i]);	
	
	printf("\n");


	free(m1);
	free(m2);

	return 0;
}
