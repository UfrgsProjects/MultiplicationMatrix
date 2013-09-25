#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

	FILE* file_tempo, *file_saida;
	int i;
	char buffer[32];
	char leitor[15];
	char buffer_saida[32];
	float amostra, acc;
	int n;

	file_saida = fopen(argv[1],"w");
	
	for (i=1;i<100;i++){
	n = 0;
	acc = 0;
	snprintf(buffer, sizeof(char) * 32, "%i.txt", i);
	file_tempo = fopen(buffer,"r");
		while(fgets(leitor,15,file_tempo)){
		amostra = atof(leitor);
			if(amostra > 0){
			acc = acc + amostra;
			n++;
			}
		}
	fprintf(file_saida,"%d %f \n",i,(acc/n));
	} 

return 0;
}
