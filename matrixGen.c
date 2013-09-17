#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, const char *argv[]){

	int i,j,r,c;
	char path[80];
	r = atoi(argv[1]);	
	c = atoi(argv[2]);	
	strcpy(path, argv[3]);
	
	
	
	srand(time(NULL));
	FILE* file = fopen(path,"w");
	
	fprintf(file, "LINHAS = %d\n", r);
	fprintf(file, "COLUNAS = %d", c);
	
	clock_t start = clock();
	for(i = 0; i < r ; i++){
		fprintf(file, "\n");
		for(j = 0; j < c ; j++)
			fprintf(file,"%d ",rand()%10);
	}
	clock_t end = clock();
	float seconds = (float)( (end - start) * 1000) / CLOCKS_PER_SEC;
	
	printf("tempo %f", seconds);
	
	fclose(file);
	
	return 0;
}
