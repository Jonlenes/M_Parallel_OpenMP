#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

/* count sort serial */
double count_sort_parallel(double a[], int n, int countThreads) {
	int i, j, count;
	double *temp;
	double start, end, duracao;

	temp = (double *)malloc(n*sizeof(double));

	start = omp_get_wtime();
	/* como os elementos podem ser contados independetimente, 
	este for pode ser paralelizado. */
	#pragma omp parallel for num_threads(countThreads) private(i, j, count)
	for (i = 0; i < n; i++) {
		count = 0;
		for (j = 0; j < n; j++)
			if (a[j] < a[i])
				count++;
			else if (a[j] == a[i] && j < i)
				count++;
		
		#pragma omp critical
		temp[count] = a[i];
	}
	end = omp_get_wtime();

	duracao = end - start;

	memcpy(a, temp, n*sizeof(double));
	free(temp);

	return duracao;
}

int main(int argc, char * argv[]) {
	int countThreads, n;

	scanf("%d", &countThreads); 	/* numero de threads */
	scanf("%d", &n); 				/* numero de valores */

	/* aloca os vetores de valores para o teste em serial(b) e para o teste em paralelo(a) */
	double *vet = (double *)malloc(n * sizeof(double));

	/* entrada dos valores */
	for(int i = 0; i < n; i++)
		scanf("%lf", &vet[i]);
	
	/* chama as funcoes de count sort em paralelo e em serial */
	double t_s = count_sort_parallel(vet, n, countThreads);
	
	/* Imprime o vetor ordenado */
	for (int i = 0; i < n; i++)
		printf("%.2lf ", vet[i]);

	printf("\n");

	/* imprime os tempos obtidos e o speedup */
	printf("%lf\n", t_s);

	return 0;
}
