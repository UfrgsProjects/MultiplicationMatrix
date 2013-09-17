#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

Matrix* init_matrix(int row, int column){
	int i = 0;	
	Matrix* matrix = (Matrix*) malloc( sizeof(Matrix) );

	matrix->row = row;
	matrix->column = column;
	matrix->value = (int **) malloc( row * sizeof(int*) );
	
	for(i = 0; i < row; i++)
		matrix->value[i] = (int *) malloc( column * sizeof(int) );
	
	return matrix;
}


Matrix* read_arquive(char *path){

	FILE* file = fopen(path,"r");
	Matrix* matrix; 
	int row = 0, column = 0, i = 0, j = 0;
	char text[80];

	if(file == NULL){
		printf("Error to read File!!!");
		exit(0);
	}
    
	// Read dimensions from matrix
	fscanf(file, "%s %s %d", text, text, &row);
	fscanf(file, "%s %s %d", text, text, &column);
	
	
	// Inicialize dinamic bidimensional vector 
    matrix = init_matrix(row, column);
	
	
	matrix->value[0][0] = 10;
	

	// Read values of matrix
	for(i = 0; i < matrix->row; i++)
		for(j = 0; j < matrix->column; j++)
			fscanf(file, "%d", &matrix->value[i][j]);
			
	fclose(file);
	return matrix;
}


int* getRowMatrix(Matrix* matrix, int index){
	return matrix->value[index];
}

int* getColumnMatrix(Matrix* matrix, int index){
	int i = 0;
	int* col = malloc(matrix->row * sizeof(int));

	for(i = 0; i < matrix->row; i++)
		col[i] = matrix->value[i][index];

	return col;

}

void init(Matrix* matrix, int row, int column){
	int i = 0;	
	
	matrix->row = row;
	matrix->column = column;
	
	matrix->value = malloc( row * sizeof(int) );
	
	for(i = 0; i < row; i++)
		matrix->value[i] = malloc( column * sizeof(int) );
}

void write_arquive(char *path, Matrix *matrix){

	FILE* file = fopen(path,"w");
	int i,j;
	
	fprintf(file, "LINHAS = %d\n", matrix->row);
	fprintf(file, "COLUNAS = %d", matrix->column);
	for(i = 0; i < matrix->row ; i++){
		fprintf(file, "\n");
		for(j = 0; j < matrix->column ; j++)
			fprintf(file,"%d ",matrix->value[i][j]);
	}
	
}
