#include <stdio.h>
#include <malloc.h>
#include <string.h>

int add_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {
	int i, min, max;
	min = (len1 < len2) ? len1 : len2;
	max = (len1 > len2) ? len1 : len2;
	*total = malloc(sizeof(int) * max);
	for(i = 0; i < min; i++) {
		(*total)[i] = arr1[i] + arr2[i];
	}
	for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {
		(*total)[i] = pMax[i];
	}
	return max;
}

int sub_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {
	int i, min, max;
	min = (len1 < len2) ? len1 : len2;
	max = (len1 > len2) ? len1 : len2;
	*total = malloc(sizeof(int) * max);
	for(i = 0; i < min; i++) {
		(*total)[i] = arr1[i] - arr2[i];
	}
	for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {
		(*total)[i] = pMax[i] * ((len1 > len2) ? 1 : -1);
	}
	return max;
}

int mul_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {
	int i, min, max;
	min = (len1 < len2) ? len1 : len2;
	max = (len1 > len2) ? len1 : len2;
	*total = malloc(sizeof(int) * max);
	for(i = 0; i < min; i++) {
		(*total)[i] = arr1[i] * arr2[i];
	}
	for(;i < max; i++) {
		(*total)[i] = 0;
	}
	return max;
}

int div_arrays(int *arr1, int len1, int *arr2, int len2, int** total) {
	int i, min, max;
	min = (len1 < len2) ? len1 : len2;
	max = (len1 > len2) ? len1 : len2;
	*total = malloc(sizeof(int) * max);
	for(i = 0; i < min; i++) {
		(*total)[i] = arr1[i] / arr2[i];
	}
	for(int *pMax = ((len1 > len2) ? arr1 : arr2);i < max; i++) {
		(*total)[i] = ((len1 > len2) ? (pMax[i] / 0) : (0 / pMax[i]));
	}
	return max;
}

int dot_product_arrays(int *arr1, int len1, int *arr2, int len2) {
	int sum = 0;
	for(int i = 0; i < ((len1 < len2) ? len1 : len2); i++) {
		sum += arr1[i] * arr2[i];
	}
	return sum;
}

int main() {
	int **ts = NULL;
	int *ls = NULL;
	int lts = 0;

	int* a = NULL;
	int* b = NULL;
	int n;
	lts++;
	ts = realloc(ts, sizeof(int*) * lts);
	ls = realloc(ls, sizeof(int) * lts);
	ls[lts - 1] = 4;
	ts[lts - 1] = malloc(sizeof(int)*ls[lts-1]);
	memcpy(ts[lts - 1], (int[]){1, 2, 3, 4}, sizeof(int) * ls[lts - 1]);
	a = realloc(a, sizeof(int) * ls[lts - 1]);
	for(int i = 0; i < ls[lts - 1]; i++) {
		a[i] = ts[lts - 1][i];
	}
	lts++;
	ts = realloc(ts, sizeof(int*) * lts);
	ls = realloc(ls, sizeof(int) * lts);
	ls[lts - 1] = 4;
	ts[lts - 1] = malloc(sizeof(int)*ls[lts-1]);
	memcpy(ts[lts - 1], (int[]){1, 2, 3, 4}, sizeof(int) * ls[lts - 1]);
	lts++;
	ts = realloc(ts, sizeof(int*) * lts);
	ls = realloc(ls, sizeof(int) * lts);
	ls[lts - 1] = div_arrays(a, 4, ts[1], 4, &(ts[lts - 1]));	b = realloc(b, sizeof(int) * ls[lts - 1]);
	for(int i = 0; i < ls[lts - 1]; i++) {
		b[i] = ts[lts - 1][i];
	}
	lts++;
	ts = realloc(ts, sizeof(int*) * lts);
	ls = realloc(ls, sizeof(int) * lts);
	ls[lts - 1] = 4;
	ts[lts - 1] = malloc(sizeof(int)*ls[lts-1]);
	memcpy(ts[lts - 1], (int[]){1, 1, 1, 1}, sizeof(int) * ls[lts - 1]);
	lts++;
	ts = realloc(ts, sizeof(int*) * lts);
	ls = realloc(ls, sizeof(int) * lts);
	ls[lts - 1] = 1;
	ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);
	*ts[lts - 1] = dot_product_arrays(b, 4, ts[3], 4);
	n = *ts[4];
	printf("%d\n", n);

	free(a);
	free(b);
	free(ts[0]);
	free(ts[1]);
	free(ts[2]);
	free(ts[3]);
	free(ls);
	free(ts);
}
