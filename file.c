/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:48:11 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/19 12:48:11 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_file(int end[2], char **argv)
{
	int	fd;

	close(end[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 fd -> stdin");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	if (dup2(end[1], STDOUT_FILENO) < 0)
	{
		perror("dup2 end[1] -> stdout");
		exit(EXIT_FAILURE);
	}
	close(end[1]);
}
