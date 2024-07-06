#include "../includes/pipex.h"

int	main(void)
{
	int	fd;
	int	fdout;
	char *line;

	fd = open("infile", O_RDONLY);
	if (fd == -1)
		return (0);
	fdout = open("out", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fdout == -1)
		return (0);
	line = get_next_line_new(fd);
	if (!line)
		return (0);
	while (line)
	{
		ft_putstr_fd(line, fdout);
		free(line);
		line = get_next_line_new(fd);
	}
	return (0);
}
