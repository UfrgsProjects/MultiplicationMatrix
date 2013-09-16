
/**
	Estrutura representativa dos dados 
	adquiridos do arquivo
*/

typedef struct matrix{
	int row;
	int column;
	int** value;
}Matrix;

// Inicializa vetor bidimensional da matrix
Matrix* init_matrix(int row, int column);

// Lê arquivo e retorna uma estrutura matrix
Matrix* read_arquive(char *path);

// Toma Linha de uma determina matrix
int* getRowMatrix(Matrix* matrix, int index);

// Toma coluna de uma determinada matrix
int* getColumnMatrix(Matrix* matrix, int index);

// Outro tipo de inicialização
void init(Matrix* matrix, int row, int column);

// TODO Escrever matrix Resultate 
int write_arquive(char *path, Matrix *matrix);
