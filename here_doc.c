/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <yel-mens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:23:25 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/24 19:15:37 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_read_line(int fd)
{
	char	buffer[2];
	char	*line;
	char	*temp;
	int		res;

	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = 0;
	buffer[1] = 0;
	buffer[0] = 0;
	while (buffer[0] != '\n')
	{
		res = read(fd, buffer, 1);
		if (res <= 0 || res == EOF)
		{
			free(line);
			return (NULL);
		}
		temp = line;
		line = ft_strjoin(line, buffer);
		free(temp);
	}
	return (line);
}

int	here_doc(char *limiter, t_cmd *cmd, char **path)
{
	pid_t	pid;
	int		end[2];
	int		new_end[2];
	char	*line;

	if (pipe(end) < 0)
		return (0);
	pid = fork();
	if (!pid)
	{
		close(end[0]);
		write(1, "here_doc> ", 10);
		line = ft_read_line(STDIN_FILENO);
		while (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			{
				free(line);
				ft_free_struct(cmd, path);
				exit(EXIT_SUCCESS);
			}
			write(end[1], line, ft_strlen(line));
			write(1, "here_doc> ", 10);
			free(line);
			line = ft_read_line(STDIN_FILENO);
		}
		ft_free_struct(cmd, path);
		exit(EXIT_FAILURE);
	}
	close(end[1]);
	waitpid(pid, NULL, 0);
	if (pipe(new_end) < 0)
		return (0);
	cmd->in = end[0];
	cmd->out = new_end[1];
	cmd->read_out = new_end[0];
	return (1);
}
