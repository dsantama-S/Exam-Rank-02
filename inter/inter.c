#include <unistd.h>

void 	ft_putchar(char c)
{
	write(1, &c, 1);
}

int 	main(int argc, char **argv)
{
	int i;
	int j;
	int n;
	int repeated;

	if (argc == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			j = 0;
			n = 0;
			repeated = 0;
			while (j < i)
			{
				if (argv[1][i] == argv[1][j])
					break ;
				j++;
			}
			while (argv[2][n])
			{
				if (argv[1][i] == argv[2][n])
				{
					repeated = 1;
				}
				n++;
			}
			if (i == j && repeated == 1)
				ft_putchar(argv[1][i]);
			i++;
		}
	}
	ft_putchar('\n');
}