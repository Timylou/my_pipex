/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:53:30 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/20 00:09:14 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec(char *cmd, char *cmd_path, char **env)
{
	char	**args;
	char	*arg;
	char	*complete_path;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	arg = ft_strjoin("/", args[0]);
	complete_path = ft_strjoin(cmd_path, arg);
	free(arg);
	free(cmd_path);
	if (execve(complete_path, args, env) < 0)
	{
		free(args);
		free(complete_path);
		perror("execve on child process");
		exit(EXIT_FAILURE);
	}
	(void) env;
	ft_free_array(args);
	free(complete_path);
}

void	ft_child_process(int end[2], char **argv, char **env)
{
	char	*cmd;

	ft_child_file(end, argv);
	cmd = ft_get_cmd_path(argv[2], env);
	if (!cmd)
	{
		perror("Did not find path to this command");
		exit(EXIT_FAILURE);
	}
	ft_exec(argv[2], cmd, env);
}

void	ft_parent_process(int end[2], pid_t pid, char **argv, char **env)
{
	char	*cmd;
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
	{
		close(end[0]);
		close(end[1]);
		exit(EXIT_FAILURE);
	}
	ft_parent_file(end, argv);
	cmd = ft_get_cmd_path(argv[3], env);
	if (!cmd)
	{
		perror("Did not find path to this command");
		exit(EXIT_FAILURE);
	}
	ft_exec(argv[3], cmd, env);
}
