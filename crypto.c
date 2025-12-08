#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	int i = 0;
	while (argv[1][i])
	{
		printf("%c", (argv[1][i] - i));
		i++;
	}
	printf("\n");
	return 0;
}