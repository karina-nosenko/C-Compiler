#include <stdio.h>
#include <stdlib.h>

int main()
{
	int* a;
	int* b;
	[4,5,6] = (int*)calloc(4, sizeof(int));
	int* t0 = (int*)malloc(sizeof(int) * 4);
	for(int i=0; i<4; i++) {
		t0[i] = [1,2,3,8][i] + [4,5,6][i];
	}
	a = t0;
	free(t0);
}
