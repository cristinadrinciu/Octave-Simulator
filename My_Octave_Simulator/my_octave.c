#include <stdio.h>
#include <stdlib.h>
#define MOD 10007

void adaug(int ****adresa_colectie, int *nr_matrici, int ***adresa_dimensiuni)
{
	int nr_linii, nr_col;
	scanf("%d%d", &nr_linii, &nr_col);
	if (nr_linii >= 1 && nr_col >= 1) {
		int i, j;
		(*nr_matrici)++;
		// adaugam dimensiunile in matricea de dimensiuni
		(*adresa_dimensiuni) = (int **)realloc((*adresa_dimensiuni),
												(*nr_matrici) * sizeof(int *));
		(*adresa_dimensiuni)[(*nr_matrici) - 1] =
		(int *)malloc(2 * sizeof(int));
		(*adresa_dimensiuni)[(*nr_matrici) - 1][0] = nr_linii;
		(*adresa_dimensiuni)[(*nr_matrici) - 1][1] = nr_col;
		// alocam memorie pentru noua matrice
		(*adresa_colectie) = (int ***)realloc((*adresa_colectie),
												(*nr_matrici) * sizeof(int **));
		(*adresa_colectie)[(*nr_matrici) - 1] =
		(int **)malloc((nr_linii) * sizeof(int *));
		for (i = 0; i < nr_linii; i++) {
			(*adresa_colectie)[(*nr_matrici) - 1][i] =
				(int *)malloc((nr_col) * sizeof(int));
		}
		for (i = 0; i < nr_linii; i++)
			for (j = 0; j < nr_col; j++)
				scanf("%d", &(*adresa_colectie)[(*nr_matrici) - 1][i][j]);
	}
}

void size(int nr_matrici, int **dimensiuni)
{
	int k;
	scanf("%d", &k);
	if (k < nr_matrici && k >= 0)
		printf("%d %d\n", dimensiuni[k][0], dimensiuni[k][1]);
	else
		printf("No matrix with the given index\n");
}

void afis(int ***colectie, int **dimensiuni, int nr_matrici)
{
	int i, j, k;
	scanf("%d", &k);
	if (k < nr_matrici && k >= 0) {
		for (i = 0; i < dimensiuni[k][0]; i++) {
			for (j = 0; j < dimensiuni[k][1]; j++)
				printf("%d ", colectie[k][i][j]);
			printf("\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

void realocare(int ****adresa_colectie, int ***adresa_dimensiuni,
			   int nr_matrici)
{
	int *v1, *v2, i, j, **a, k, l, c;
	scanf("%d", &k);
	scanf(" %d", &l);
	v1 = (int *)malloc(l * sizeof(int));
	// se citesc liniile folosite
	for (i = 0; i < l; i++)
		scanf(" %d", &v1[i]);
	scanf(" %d", &c);
	v2 = (int *)malloc(c * sizeof(int));
	// se citesc coloanelor folosite
	for (i = 0; i < c; i++)
		scanf(" %d", &v2[i]);
	if (k >= nr_matrici || k < 0) {
		printf("No matrix with the given index\n");
		// eliberam vectorii auxiliari
		free(v1);
		free(v2);
		return;
	}
	// alocam o matrice auxiliara
	a = (int **)malloc(l * sizeof(int *));
	for (i = 0; i < l; i++)
		a[i] = (int *)malloc(c * sizeof(int));
	// mutam elementele corespunzatoare in matricea aux
	for (i = 0; i < l; i++)
		for (j = 0; j < c; j++)
			a[i][j] = (*adresa_colectie)[k][v1[i]][v2[j]];
	// eliberez matricea originala
	for (i = 0; i < (*adresa_dimensiuni)[k][0]; i++)
		free((*adresa_colectie)[k][i]);
	free((*adresa_colectie)[k]);
	// realocam matricea
	(*adresa_colectie)[k] = (int **)malloc(l * sizeof(int *));
	for (i = 0; i < l; i++)
		(*adresa_colectie)[k][i] = (int *)malloc(c * sizeof(int));
	// atribuim valorile
	for (i = 0; i < l; i++)
		for (j = 0; j < c; j++)
			(*adresa_colectie)[k][i][j] = a[i][j];
	// modificam dimensiunile in matricea de dimensiui
	(*adresa_dimensiuni)[k][0] = l;
	(*adresa_dimensiuni)[k][1] = c;
	// eliberam vectorii auxiliari
	free(v1);
	free(v2);
	// eliberam matricea auxiliara
	for (i = 0; i < l; i++)
		free(a[i]);
	free(a);
}

void inmultire(int ****colectie, int ***dimensiuni,
			   int *nr_matrici)
{
	int i, j, k, **a;
	int m, n;
	scanf("%d%d", &m, &n);
	if (m >= (*nr_matrici) || n >= (*nr_matrici) || m < 0 || n < 0) {
		printf("No matrix with the given index\n");
	} else {
		if ((*dimensiuni)[m][1] != (*dimensiuni)[n][0]) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			(*nr_matrici)++;
			// alocam o matrice auxiliare pt inmultire
			a = (int **)calloc((*dimensiuni)[m][0], sizeof(int *));
			for (i = 0; i < (*dimensiuni)[m][0]; i++)
				a[i] = (int *)calloc((*dimensiuni)[n][1], sizeof(int));
			// efectuam inmultirea
			for (i = 0; i < (*dimensiuni)[m][0]; i++)
				for (j = 0; j < (*dimensiuni)[n][1]; j++)
					for (k = 0; k < (*dimensiuni)[n][0]; k++) {
						a[i][j] += ((*colectie)[m][i][k] *
									(*colectie)[n][k][j]) %
									MOD;
						a[i][j] = ((a[i][j] % MOD) + MOD) % MOD;
					}
			// adaugam dimensiunile in matricea de dimensiuni
			(*dimensiuni) = (int **)realloc((*dimensiuni),
						 (*nr_matrici) * sizeof(int *));
			(*dimensiuni)[(*nr_matrici) - 1] =
				(int *)malloc(2 * sizeof(int));
			(*dimensiuni)[(*nr_matrici) - 1][0] =
				(*dimensiuni)[m][0];
			(*dimensiuni)[(*nr_matrici) - 1][1] =
				(*dimensiuni)[n][1];
			// alocam memorie pentru noua matrice
			(*colectie) = (int ***)realloc((*colectie),
						(*nr_matrici) * sizeof(int **));
			(*colectie)[(*nr_matrici) - 1] =
				(int **)malloc((*dimensiuni)[m][0] * sizeof(int *));
			for (i = 0; i < (*dimensiuni)[m][0]; i++) {
				(*colectie)[(*nr_matrici) - 1][i] =
					(int *)malloc((*dimensiuni)[n][1] * sizeof(int));
			}
			// egalam matricea noua cu matricea inmultirii
			for (i = 0; i < (*dimensiuni)[m][0]; i++)
				for (j = 0; j < (*dimensiuni)[n][1]; j++)
					(*colectie)[(*nr_matrici) - 1][i][j] = a[i][j];
			// eliberam matricea auxiliara
			for (i = 0; i < (*dimensiuni)[m][0]; i++)
				free(a[i]);
			free(a);
		}
	}
}

void swap_matrix(int ***a, int ***b)
{
	int **aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

int suma(int ***colectie, int **dimensiuni, int k)
{
	// calculam suma elementelor unei matrici
	int i, j, S = 0;
	for (i = 0; i < dimensiuni[k][0]; i++)
		for (j = 0; j < dimensiuni[k][1]; j++) {
			S += colectie[k][i][j] % MOD;
			S = ((S % MOD) + MOD) % MOD;
		}

	return S;
}

void swap_array(int **a, int **b)
{
	int *aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void sortare(int ****adresa_colectie, int ***adresa_dimensiuni,
			 int nr_matrici)
{
	int i, j;
	for (i = 0; i < nr_matrici - 1; i++)
		for (j = i + 1; j < nr_matrici; j++)
			if (suma((*adresa_colectie), (*adresa_dimensiuni), i) >
				suma((*adresa_colectie), (*adresa_dimensiuni), j)) {
				swap_matrix(&((*adresa_colectie)[i]), &((*adresa_colectie))[j]);
				swap_array(&((*adresa_dimensiuni)[i]),
						   &((*adresa_dimensiuni)[j]));
			}
}

void multiply(int **a, int **b, int n)
{
	int i, j, k, **c;
	// alocam matricea pt imultire
	c = (int **)calloc(n, sizeof(int *));
	for (i = 0; i < n; i++)
		c[i] = (int *)calloc(n, sizeof(int));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			c[i][j] = 0;
			for (k = 0; k < n; k++) {
				c[i][j] += (a[i][k] * b[k][j]) % MOD;
				c[i][j] = ((c[i][j] % MOD) + MOD) % MOD;
			}
		}
	// atribuim matricei 1 adica matricea inmultire
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = c[i][j];
	// eliberam matricea inmultire
	for (i = 0; i < n; i++)
		free(c[i]);
	free(c);
}

void putere(int ***colectie, int **dimensiuni, int nr_matrici)
{
	int k, p;
	scanf("%d%d", &k, &p);
	if (k >= nr_matrici || k < 0) {
		printf("No matrix with the given index\n");
	} else {
		if (p < 0) {
			printf("Power should be positive\n");
		} else {
			if (dimensiuni[k][0] != dimensiuni[k][1]) {
				printf("Cannot perform matrix multiplication\n");
			} else {
				int **aux, i, j;
				// alocam o matrice auxiliara pentru putere
				aux = (int **)calloc(dimensiuni[k][0], sizeof(int *));
				for (i = 0; i < dimensiuni[k][0]; i++)
					aux[i] = (int *)calloc(dimensiuni[k][1], sizeof(int));
				// o egalam cu matricea originala
				for (i = 0; i < dimensiuni[k][0]; i++)
					for (j = 0; j < dimensiuni[k][0]; j++)
						aux[i][j] = colectie[k][i][j];
				// matricea este deja la puterea 1
				p--;
				while (p > 0) {
					if (p % 2 == 1)
						multiply(colectie[k], aux, dimensiuni[k][0]);
					multiply(aux, aux, dimensiuni[k][0]);
					p /= 2;
				}
				// eliberam matricea auxiliara
				for (i = 0; i < dimensiuni[k][0]; i++)
					free(aux[i]);
				free(aux);
			}
		}
	}
}

void traspunere(int ****adresa_colectie, int ***adresa_dimensiuni,
				int nr_matrici)
{
	int i, j, k;
	scanf("%d", &k);
	if (k >= nr_matrici || k < 0) {
		printf("No matrix with the given index\n");
	} else {
		int **a;
		// alocam o matrice auxiliara cu dimensiunile de transpunere
		a = (int **)malloc((*adresa_dimensiuni)[k][1] * sizeof(int *));
		for (i = 0; i < (*adresa_dimensiuni)[k][1]; i++)
			a[i] = (int *)malloc((*adresa_dimensiuni)[k][0] * sizeof(int));
		// costruim transpusa
		for (i = 0; i < (*adresa_dimensiuni)[k][0]; i++)
			for (j = 0; j < (*adresa_dimensiuni)[k][1]; j++)
				a[j][i] = (*adresa_colectie)[k][i][j];
		// eliberam matricea initiala
		for (i = 0; i < (*adresa_dimensiuni)[k][0]; i++)
			free((*adresa_colectie)[k][i]);
		free((*adresa_colectie)[k]);
		// alocam iar matricea pt transpunere
		(*adresa_colectie)[k] =
			(int **)malloc((*adresa_dimensiuni)[k][1] * sizeof(int *));
		for (i = 0; i < (*adresa_dimensiuni)[k][1]; i++)
			(*adresa_colectie)[k][i] =
				(int *)malloc((*adresa_dimensiuni)[k][0] * sizeof(int));
		// egalam elementele
		for (i = 0; i < (*adresa_dimensiuni)[k][1]; i++)
			for (j = 0; j < (*adresa_dimensiuni)[k][0]; j++)
				(*adresa_colectie)[k][i][j] = a[i][j];
		// interschimbam dimensiunile
		int aux;
		aux = (*adresa_dimensiuni)[k][0];
		(*adresa_dimensiuni)[k][0] = (*adresa_dimensiuni)[k][1];
		(*adresa_dimensiuni)[k][1] = aux;
		// eliberam matricea auxiliara
		for (i = 0; i < (*adresa_dimensiuni)[k][0]; i++)
			free(a[i]);
		free(a);
	}
}

void eliberare(int ****adresa_colectie, int ***adresa_dimensiuni,
			   int *nr_matrici)
{
	int i;
	int k;
	scanf("%d", &k);
	if (k >= *nr_matrici || k < 0) {
		printf("No matrix with the given index\n");
	} else {
		// mutam matricea care se elibereaza la finalul sirului
		for (i = k; i < *nr_matrici - 1; i++) {
			swap_matrix(&((*adresa_colectie)[i]), &((*adresa_colectie))[i + 1]);
			swap_array(&((*adresa_dimensiuni)[i]),
					   &((*adresa_dimensiuni)[i + 1]));
		}
		// eliberam matricea
		for (i = 0; i < (*adresa_dimensiuni)[(*nr_matrici) - 1][0]; i++)
			free((*adresa_colectie)[((*nr_matrici) - 1)][i]);
		free((*adresa_colectie)[(*nr_matrici) - 1]);
		// eliberam dimensiunile de la matricea eliberata
		free((*adresa_dimensiuni)[(*nr_matrici) - 1]);
		// realocam colectia de matrici
		(*nr_matrici)--;
		(*adresa_colectie) = (int ***)realloc((*adresa_colectie),
												(*nr_matrici) * sizeof(int **));
		// realocam matricea cu dimensiuni
		(*adresa_dimensiuni) = (int **)realloc((*adresa_dimensiuni),
												(*nr_matrici) * sizeof(int *));
	}
}

void iesire(int ****adresa_colectie, int ***adresa_dimensiuni,
			int *nr_matrici)
{
	int i, j;
	// eliberam colectia de matrice
	for (i = 0; i < (*nr_matrici); i++) {
		for (j = 0; j < (*adresa_dimensiuni)[i][0]; j++)
			free((*adresa_colectie)[i][j]);
		free((*adresa_colectie)[i]);
	}
	free(*adresa_colectie);
	// eliberam matricea de dimensiuni
	for (int i = 0; i < (*nr_matrici); i++)
		free((*adresa_dimensiuni)[i]);
	free(*adresa_dimensiuni);
	*nr_matrici = 0;
}

void adun(int **a, int **b, int **c, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			c[i][j] = (a[i][j] + b[i][j]) % MOD;
			c[i][j] = ((c[i][j] % MOD) + MOD) % MOD;
		}
}

void scad(int **a, int **b, int **c, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			c[i][j] = (a[i][j] - b[i][j]) % MOD;
			c[i][j] = ((c[i][j] % MOD) + MOD) % MOD;
		}
}

int putere2(int x)
{
	if (x % 2 == 1)
		return 0;
	if (x == 1)
		return 1;
	while (x % 2 == 0)
		x /= 2;
	if (x == 1)
		return 1;
	return 0;
}

void alocare(int ***a, int dim1, int dim2)
{
	int i;
	*a = (int **)malloc(dim1 * sizeof(int *));
	for (i = 0; i < dim1; i++)
		(*a)[i] = (int *)malloc(dim2 * sizeof(int));
}

void strassen(int **a, int **b, int **c, int dim)
{
	if (dim == 1) {
		c[0][0] = (a[0][0] * b[0][0]) % MOD;
		c[0][0] = ((c[0][0] % MOD) + MOD) % MOD;
	} else {
		int i, j;
		int dim2 = dim / 2;
		int ***M;
		M = (int ***)malloc(21 * sizeof(int **));
		for (i = 0; i < 21; i++)
			alocare(&M[i], dim2, dim2);
		// M0-3 pt a, M4-7 pt b, M8-11 pt c, M12-18 pt p, M19 pt a_aux, M20 pt
		// b_aux
		for (i = 0; i < dim2; i++) {
			for (j = 0; j < dim2; j++) {
				M[0][i][j] = a[i][j];                // a11
				M[1][i][j] = a[i][j + dim2];         // a12
				M[2][i][j] = a[i + dim2][j];         // a21
				M[3][i][j] = a[i + dim2][j + dim2];  // a22
				M[4][i][j] = b[i][j];                // b11
				M[5][i][j] = b[i][j + dim2];         // b12
				M[6][i][j] = b[i + dim2][j];         // b21
				M[7][i][j] = b[i + dim2][j + dim2];  // b22
			}
		}
		adun(M[0], M[3], M[19], dim2);        // a11 + a22
		adun(M[4], M[7], M[20], dim2);        // b11 + b22
		strassen(M[19], M[20], M[12], dim2);  // p1 = (a11+a22) * (b11+b22)
		adun(M[2], M[3], M[19], dim2);        // a21 + a22
		strassen(M[19], M[4], M[13], dim2);   // p2 = (a21+a22) * (b11)
		scad(M[5], M[7], M[20], dim2);        // b12 - b22
		strassen(M[0], M[20], M[14], dim2);   // p3 = (a11) * (b12 - b22)
		scad(M[6], M[4], M[20], dim2);        // b21 - b11
		strassen(M[3], M[20], M[15], dim2);   // p4 = (a22) * (b21 - b11)
		adun(M[0], M[1], M[19], dim2);        // a11 + a12
		strassen(M[19], M[7], M[16], dim2);   // p5 = (a11+a12) * (b22)
		scad(M[2], M[0], M[19], dim2);        // a21 - a11
		adun(M[4], M[5], M[20], dim2);        // b11 + b12
		strassen(M[19], M[20], M[17], dim2);  // p6 = (a21-a11) * (b11+b12)
		scad(M[1], M[3], M[19], dim2);        // a12 - a22
		adun(M[6], M[7], M[20], dim2);        // b21 + b22
		strassen(M[19], M[20], M[18], dim2);  // p7 = (a12-a22) * (b21+b22)
		adun(M[14], M[16], M[9], dim2);       // c12 = p3 + p5
		adun(M[13], M[15], M[10], dim2);      // c21 = p2 + p4
		adun(M[12], M[15], M[19], dim2);      // p1 + p4
		adun(M[19], M[18], M[20], dim2);      // p1 + p4 + p7
		scad(M[20], M[16], M[8], dim2);       // c11 = p1 + p4 - p5 + p7
		adun(M[12], M[14], M[19], dim2);      // p1 + p3
		adun(M[19], M[17], M[20], dim2);      // p1 + p3 + p6
		scad(M[20], M[13], M[11], dim2);      // c22 = p1 + p3 - p2 + p6
		for (i = 0; i < dim2; i++) {
			for (j = 0; j < dim2; j++) {
				c[i][j] = M[8][i][j];
				c[i][j + dim2] = M[9][i][j];
				c[i + dim2][j] = M[10][i][j];
				c[i + dim2][j + dim2] = M[11][i][j];
			}
		}
		for (i = 0; i < 21; i++) {
			for (j = 0; j < dim2; j++)
				free(M[i][j]);
			free(M[i]);
		}
		free(M);
	}
}

void bonus(int ****adresa_colectie, int ***adresa_dimensiuni, int *nr_matrici)
{
	int a, b;
	scanf("%d%d", &a, &b);
	if (a >= (*nr_matrici) || b >= (*nr_matrici) || a < 0 || b < 0) {
		printf("No matrix with the given index\n");
	} else {
		if ((*adresa_dimensiuni)[a][0] != (*adresa_dimensiuni)[a][1] ||
			(*adresa_dimensiuni)[b][0] != (*adresa_dimensiuni)[b][1] ||
			(*adresa_dimensiuni)[a][0] != (*adresa_dimensiuni)[b][0] ||
			putere2((*adresa_dimensiuni)[a][0]) == 0) {
			printf("Cannot perform matrix multiplication\n");
			} else {
				(*nr_matrici)++;
				int i;
				// adaugam dimensiunile in matricea de dimensiuni
				(*adresa_dimensiuni) = (int **)realloc((*adresa_dimensiuni),
				 (*nr_matrici) * sizeof(int *));
				(*adresa_dimensiuni)[(*nr_matrici) - 1] =
					(int *)malloc(2 * sizeof(int));
				(*adresa_dimensiuni)[(*nr_matrici) - 1][0] =
					(*adresa_dimensiuni)[a][0];
				(*adresa_dimensiuni)[(*nr_matrici) - 1][1] =
					(*adresa_dimensiuni)[a][1];
				// alocam memorie pentru noua matrice
				(*adresa_colectie) = (int ***)realloc((*adresa_colectie),
				 (*nr_matrici) * sizeof(int **));
				(*adresa_colectie)[(*nr_matrici) - 1] =
					(int **)malloc((*adresa_dimensiuni)[a][0] * sizeof(int *));
				for (i = 0; i < (*adresa_dimensiuni)[a][0]; i++) {
					(*adresa_colectie)[(*nr_matrici) - 1][i] =
						(int *)malloc((*adresa_dimensiuni)[a][1] * sizeof(int));
				}
				// efectuam inmultirea in matricea noua
				strassen((*adresa_colectie)[a], (*adresa_colectie)[b],
						 (*adresa_colectie)[(*nr_matrici) - 1],
						 (*adresa_dimensiuni)[a][0]);
		}
	}
}

int main(void)
{
	int ***colectie, **dimensiuni, nr_matrici;
	nr_matrici = 0;
	colectie = (int ***)malloc(1 * sizeof(int **));
	dimensiuni = (int **)malloc(1 * sizeof(int *));
	char x;
	while (1) {
		scanf(" %c", &x);
		if (x == 'L' || x == 'D' || x == 'P' || x == 'C' || x == 'M' ||
			x == 'O' || x == 'T' || x == 'R' || x == 'F' || x == 'Q' ||
			x == 'S') {
			if (x == 'L')
				adaug(&colectie, &nr_matrici, &dimensiuni);
			if (x == 'D')
				size(nr_matrici, dimensiuni);
			if (x == 'P')
				afis(colectie, dimensiuni, nr_matrici);
			if (x == 'C')
				realocare(&colectie, &dimensiuni, nr_matrici);
			if (x == 'M')
				inmultire(&colectie, &dimensiuni, &nr_matrici);
			if (x == 'O')
				sortare(&colectie, &dimensiuni, nr_matrici);
			if (x == 'T')
				traspunere(&colectie, &dimensiuni, nr_matrici);
			if (x == 'R')
				putere(colectie, dimensiuni, nr_matrici);
			if (x == 'F')
				eliberare(&colectie, &dimensiuni, &nr_matrici);
			if (x == 'S')
				bonus(&colectie, &dimensiuni, &nr_matrici);
			if (x == 'Q') {
				iesire(&colectie, &dimensiuni, &nr_matrici);
				break;
			}
		} else {
			printf("Unrecognized command\n");  
		}
	}
	return 0;
}
