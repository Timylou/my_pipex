/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <yel-mens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:23:25 by yel-mens          #+#    #+#             */
/*   Updated: 2025/02/25 14:19:34 by yel-mens         ###   ########.fr       */
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

static void	ft_read_stdin(int end[2], char *limiter, t_cmd *cmd, char **path)
{
	char	*line;
	int		len_line;

	close(end[0]);
	write(1, "here_doc> ", 10);
	line = ft_read_line(STDIN_FILENO);
	while (line)
	{
		len_line = ft_strlen(line) - 1;
		if (!ft_strncmp(line, limiter, len_line))
		{
			free(line);
			close(end[1]);
			ft_free_struct(cmd, path);
			exit(EXIT_SUCCESS);
		}
		write(end[1], line, len_line + 1);
		write(1, "here_doc> ", 10);
		free(line);
		line = ft_read_line(STDIN_FILENO);
	}
	close(end[1]);
	ft_free_struct(cmd, path);
	exit(EXIT_FAILURE);
}

int	here_doc(char *limiter, t_cmd *cmd, char **path)
{
	pid_t	pid;
	int		end[2];
	int		new_end[2];

	if (pipe(end) < 0)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		close(end[0]);
		close(end[1]);
		return (0);
	}
	if (!pid)
		ft_read_stdin(end, limiter, cmd, path);
	close(end[1]);
	waitpid(pid, NULL, 0);
	if (pipe(new_end) < 0)
		return (0);
	cmd->in = end[0];
	cmd->out = new_end[1];
	cmd->read_out = new_end[0];
	return (1);
}
