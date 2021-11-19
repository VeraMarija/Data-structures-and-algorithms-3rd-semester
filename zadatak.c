#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int* generiraj(int n) {
	int* niz = (int*)malloc(sizeof(int) * n);
	niz[0] = rand() % 5;
	int i;
	for (i = 1; i < n; i++) {
		niz[i] = niz[i - 1] + 1 + rand() % 5;
	}
	printf("\n");
	return niz;
}

void shuffle(int* niz, int n) {
	int i;
	for (i = 0; i < n; i++) {
		int j = (rand() * rand()) % n;
		int tmp = niz[i];
		niz[i] = niz[j];
		niz[j] = tmp;
	}
}

int* presjek(int* skupA, int* skupB, int n) {
	int i, j, k = 0;
	int* p = (int*)malloc(n * sizeof(int));
	if (!p)
		return NULL;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			if (skupA[i] == skupB[j]) {
				p[k] = skupA[i];
				k++;
			}
		}
	}
	return p;
}
int cmpfunc(const void* a, const void* b) {
	
	return (*(int*)a - *(int*)b);
}

int* presjek_jedan_sortiran(int *skupA, int *skupB, int n) {
	int i,j;
	int* p = (int*)malloc(n * sizeof(int));
	if (!p)
		return NULL;
	int* q;
	for (i = 0,j=0;i < n;++i) {
		q = (int*)bsearch(&skupA[i], skupB, n, sizeof(int), cmpfunc);
		if (q != NULL) {
			p[j] = *q;
			j++;
		}
	}
	return p;

}

int* presjek_oba_sortirana(int* skupA, int* skupB, int n) {
	int i, j,k=0,m;
	int* p = (int*)malloc(n * sizeof(int));
	for (i = 0,j=0;i < n;++i,j++) {
		if (skupA[i] == skupB[j]) {
			p[k] = skupA[i];
			k++;
		}
		if (skupA[i] > skupB[i] ){
			for (m=j+1;m < n;++m) {
				if (skupA[i] == skupB[m]) {
					p[k] = skupA[i];
					k++;
				}
			}
		}	
	}
	return p;
}

int main() {
	int n;
	printf("nisu sortirani");
	for (n = 10000;n < 100000;n += 30000) {
		int* skupA = generiraj(n);
		int* skupB = generiraj(n);
		shuffle(skupA, n);
		shuffle(skupB, n);
		size_t start, end;
		start = clock();
		int* p = presjek(skupA, skupB, n);
		free(p);
		end = clock();
		printf("start--%d", start);
		printf("\nend---%d", end);
		double total = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\ntotal---%lf\n", total);
	}
	
	printf("\n");
	printf("jedan sortirani");
	for (n = 10000;n < 100000;n += 30000) {
		int* skupA = generiraj(n);
		int* skupB = generiraj(n);
		shuffle(skupA, n);
		shuffle(skupB, n);
		size_t start, end;
		start = clock();
		qsort(skupB, n, sizeof(int), cmpfunc);
		int* p = presjek_jedan_sortiran(skupA, skupB, n);
		free(p);
		end = clock();
		printf("start--%d", start);
		printf("\nend---%d", end);
		double total = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\ntotal---%lf\n", total);
	}
	
	printf("\n");
	printf("oba sortirana");
	for (n = 10000;n < 100000;n += 30000) {
		int* skupA = generiraj(n);
		int* skupB = generiraj(n);
		size_t start, end;
		start = clock();
		int* p =presjek_oba_sortirana( skupA, skupB, n);
		free(p);
		end = clock();
		printf("start--%d", start);
		printf("\nend---%d", end);
		double total = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\ntotal---%lf\n", total);
	}

	return 0;

}