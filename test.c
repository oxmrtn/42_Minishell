#include "incs/minishell.h"

int	main()
{
	char	**splitted;

	char *line = get_next_line(1);
	size_t	len = ft_strlen(line);
	line[len - 1] = '\0';
	splitted = ft_split_quote(line, ' ');
	int i = 0;
	while (splitted[i])
	{
		printf("splitted[%d] = |%s| \n",i,  splitted[i]);
		i++;
	}
}