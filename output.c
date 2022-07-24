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
		if(len1 > len2) {
			fprintf(stderr, "Division by zero: longer array divided by a shorter\n");
			exit(1);
		}
		else {
			(*total)[i] = 0 / pMax[i];
		}
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

	int* fib = NULL;
	lts++;
	ts = realloc(ts, sizeof(int*) * lts);
	ls = realloc(ls, sizeof(int) * lts);
	ls[lts - 1] = 16;
	ts[lts - 1] = malloc(sizeof(int)*ls[lts-1]);
	memcpy(ts[lts - 1], (int[]){0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610}, sizeof(int) * ls[lts - 1]);
	fib = realloc(fib, sizeof(int) * ls[lts - 1]);
	for(int i = 0; i < ls[lts - 1]; i++) {
		fib[i] = ts[lts - 1][i];
	}
