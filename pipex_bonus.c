/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:47:30 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/21 16:25:07 by yel-mens         ###   ########.fr       */
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

static void	ft_loop(int end[2], int argc, char **argv, char **env)
{
	pid_t	pid;
	int		i;

	i = 2;
	while (i < argc - 2)
	{
		pid = fork();
		if (!pid)
		{
			ft_child_file(end, i, argv);
			ft_child_process(i, argv, env);
		}
		else
			ft_wait(pid, end);
		printf("caca");
		/*
		else
		{
			ft_wait(pid, end);
			ft_parent_file(end, i + 1, argc, argv);
			ft_parent_process(i + 1, argv, env);
		}*/
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	int		end[2];

	if (argc < 5)
		return (EXIT_FAILURE);
	if (pipe(end) < 0)
		return (EXIT_FAILURE);
	ft_loop(end, argc, argv, env);
	ft_parent_file(end, argc - 2, argc, argv);
	ft_parent_process(argc - 2, argv, env);
}
