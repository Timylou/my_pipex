/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:53:30 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/21 15:41:03 by yel-mens         ###   ########.fr       */
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

void	ft_child_process(int i, char **argv, char **env)
{
	char	*cmd;

	cmd = ft_get_cmd_path(argv[i], env);
	if (!cmd)
	{
		perror("Did not find path to this command");
		exit(EXIT_FAILURE);
	}
	ft_exec(argv[i], cmd, env);
	exit(EXIT_SUCCESS);

}

void	ft_parent_process(int i, char **argv, char **env)
{
	char	*cmd;

	cmd = ft_get_cmd_path(argv[i], env);
	if (!cmd)
	{
		perror("Did not find path to this command");
		exit(EXIT_FAILURE);
	}
	ft_exec(argv[i], cmd, env);
}
