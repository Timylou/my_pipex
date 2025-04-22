/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <yel-mens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:11:35 by yel-mens          #+#    #+#             */
/*   Updated: 2025/04/22 14:39:29 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_dup_files(t_cmd *cmd)
{
	if (cmd->in >= 0)
	{
		if (dup2(cmd->in, STDIN_FILENO) < 0)
		{
			perror("dup2 to stdin");
			close(cmd->in);
			close(cmd->out);
			return (0);
		}
		close(cmd->in);
	}
	if (cmd->out >= 0)
	{
		if (dup2(cmd->out, STDOUT_FILENO) < 0)
		{
			perror("dup2 to stdout");
			close(cmd->out);
			return (0);
		}
		close(cmd->out);
	}
	return (1);
}

static int	ft_exec(t_cmd *cmd, char **env)
{
	if (!cmd->args)
		return (0);
	if (execve(cmd->args[0], cmd->args, env) < 0)
		return (0);
	return (1);
}

static void	ft_close(t_cmd *all_cmd, t_cmd *cmd)
{
	while (all_cmd)
	{
		if (all_cmd != cmd)
		{
			if (all_cmd->in >= 0)
				close(all_cmd->in);
			if (all_cmd->out >= 0)
				close(all_cmd->out);
		}
		all_cmd = all_cmd->next;
	}
}

static void	ft_process(t_cmd *cmd, char **env)
{
	pid_t	pid;
	t_cmd	*all_cmd;

	all_cmd = cmd;
	while (cmd)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (!pid)
		{
			ft_close(all_cmd, cmd);
			if (!ft_dup_files(cmd))
			{
				ft_free_array(cmd->args);
				return ;
			}
			if (!ft_exec(cmd, env))
			{
				ft_free_struct(all_cmd, ft_split("useless free", ' '));
				exit(EXIT_FAILURE);
			}
		}
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;

	if (argc < 5 || (BONUS == 0 && argc != 5)
		|| (!ft_strncmp(argv[1], "here_doc", 8) && argc < 6))
		return (EXIT_FAILURE);
	cmd = ft_init_struct(argc, argv, env);
	if (!cmd)
		return (EXIT_FAILURE);
	ft_process(cmd, env);
	ft_free_struct(cmd, ft_split("useless free", ' '));
	while (wait(NULL) != -1)
		;
}
