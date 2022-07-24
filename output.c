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
			fprintf(stderr, "Division of a shorter array by a longer caused a division by zero.\n");
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

	int* a = NULL;
	int* b = NULL;
	int n;
	n = 6;
	printf("%d\n", n);

	free(ls);
	free(ts);
}
