#include <stdio.h>
#include <malloc.h>

int main() {
	int **ts = NULL;
	int *ls = NULL;
	int lts = 0;
	{
		int x;
		int y;
		int z;
		y = 0;
		z = 0;
		lts++;
		ts = realloc(ts, sizeof(int*) * lts);
		ls = realloc(ls, sizeof(int) * lts);
		ls[lts - 1] = 1;
		ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);
		ts[lts - 1][0] = 5 + 4;
		lts++;
		ts = realloc(ts, sizeof(int*) * lts);
		ls = realloc(ls, sizeof(int) * lts);
		ls[lts - 1] = 1;
		ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);
		ts[lts - 1][0] = ts[0][0] * 3;
		lts++;
		ts = realloc(ts, sizeof(int*) * lts);
		ls = realloc(ls, sizeof(int) * lts);
		ls[lts - 1] = 1;
		ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);
		ts[lts - 1][0] = ts[1][0] + 0;
		x = ts[2][0];
		while(y != 1)
		{
			printf("%d, %d, %d\n", x, y, z);
			if(x == 27)
			{
				y = 1;
				z = 2;
			}
			if(x != 27)
			{
				y = 0;
				z = 1;
				if(x < 27)
				{
					lts++;
					ts = realloc(ts, sizeof(int*) * lts);
					ls = realloc(ls, sizeof(int) * lts);
					ls[lts - 1] = 1;
					ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);
					ts[lts - 1][0] = x + 1;
					x = ts[3][0];
				}
				if(x > 27)
				{
					lts++;
					ts = realloc(ts, sizeof(int*) * lts);
					ls = realloc(ls, sizeof(int) * lts);
					ls[lts - 1] = 1;
					ts[lts - 1] = malloc(sizeof(int) * ls[lts - 1]);
					ts[lts - 1][0] = x - 1;
					x = ts[4][0];
				}
			}
		}
		printf("%d, %d, %d\n", x, y, z);
	}

	for(int i = 0; i < lts; i++) {
		free(ts[i]);
	}
	free(ls);
	free(ts);
}
