#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double subsreversa (double **matrix, double *root, const int dim) {
	int j, k, n;
	double sum;
	root[dim-1] = matrix[dim-1][dim]/matrix[dim-1][dim-1];
	k = dim-2;
	while (k>=0) {
		sum = matrix[k][dim];
		for (j=k+1; j<dim; j++) 
			sum = sum - matrix[k][j]*root[j];
		root[k] = sum/matrix[k][k];
		k--;
	}
}

void imprime(double **matrix, int dim){
	int i, j;
	printf("Matriz: \n");
	for(i=0;i<dim;i++) {
		for(j=0;j<dim+1;j++) { 
			printf("%5.2lf\t",matrix[i][j]);
		}	  
		printf("\n");
	}
	printf("\n");
}

void trocar_linhas (double *line1, double *line2, int dim) {
	double temp;
	int i;

	for (i=0; i<=dim; i++) {
		temp = line1[i];
		line1[i] = line2[i];
		line2[i] = temp;
	}
}

double **pivoteamento (double **matrix, int dim) {
	int i, j, k, test;
	double w, m, temp;

	for (k=0; k<dim; k++) {
		printf("\n\n------------ k = %d ---------------\n", k);
		test = -1;
		imprime(matrix,dim);
		w = matrix[k][k];
		for (j=k; j<dim; j++) {
			if (fabs(matrix[j][k]) > w)
					test = j;
		}
		if (test != -1) {
			trocar_linhas(matrix[k], matrix[test], dim);
			printf("\nMatriz após troca de linhas %d e %d: \n", k, test);
			imprime(matrix,dim);
		}
		for (i=k+1; i<dim; i++) {
			m = matrix[i][k]/matrix[k][k];
			for (j=k; j<=dim; j++)
				matrix[i][j] = matrix[i][j] - m*matrix[k][j];
		}
		printf("\nEstágio da matriz: \n");
		imprime(matrix,dim);
	}
	printf("\n\n ---------------- fim do pivoteamento ------------------\n\n");
	return matrix;		
}

double **ler(char *archive, int *dimension) {
	int i, j, dim;
	double **matrix, a;
	FILE *arch;

	arch = fopen(archive, "r");

	fscanf(arch,"%d",&dim);

	matrix = malloc(dim*sizeof(double *));
	for (i=0; i<dim; i++)
		matrix[i] = (double *)malloc(dim*sizeof(double));

	for(i=0; i<dim; i++)	{
		for (j=0; j<dim+1; j++)
			fscanf(arch,"%lf",&matrix[i][j]);
	}
	*dimension = dim;
	return matrix;
}

int main(int argc, char **argv) {
	double **M;
	double *raizes;
	int i, dim;

	M=ler(argv[1], &dim);
	imprime(M, dim);
	pivoteamento(M,dim);
	imprime(M, dim);
	raizes = malloc(dim*sizeof(double));
	subsreversa(M,raizes,dim);
	for (i=0; i<dim; i++)
		printf("x%1d = %5.2lf\n", i, raizes[i]);
	return 0;
}
