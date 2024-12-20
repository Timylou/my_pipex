/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:11:35 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/21 15:02:57 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_wait(pid_t pid, int end[2])
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
	{
		close(end[0]);
		close(end[1]);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		end[2];
	pid_t	pid;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (pipe(end) < 0)
		return (EXIT_FAILURE);
	pid = fork();
	if (!pid)
	{
		ft_child_file(end, 2, argv);
		ft_child_process(2, argv, env);
	}
	else
	{
		ft_wait(pid, end);
		ft_parent_file(end, 3, argc, argv);
		ft_parent_process(3, argv, env);
	}
	return (EXIT_SUCCESS);
}
