#include <stdio.h>

int main()
{
	int x;
	int y;
	int z;
	y = 0;
	z = 0;
	x = ( 5 + 4 ) * 3;
	while(y != 1)
	{
		printf("%d, %d, %d", x, y, z);
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
				x = x + 1;
			}
			if(x > 27)
			{
				x = x - 1;
			}
		}
	}
}
