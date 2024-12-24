/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <yel-mens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:47:37 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/24 18:04:43 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_open_infile(char **argv, t_cmd *cmd)
{
	int	end[2];

	cmd->in = open(argv[1], O_RDONLY);
	if (cmd->in < 0)
	{
		perror(argv[1]);
		return (0);
	}
	if (pipe(end) < 0)
	{
		perror("pipe");
		close(cmd->in);
		return (0);
	}
	cmd->out = end[1];
	cmd->read_out = end[0];
	return (1);
}

static int	ft_open_pipe(t_cmd *cmd)
{
	int	in;
	int	end[2];

	while (cmd->next)
	{
		in = cmd->read_out;
		cmd = cmd->next;
	}
	cmd->in = in;
	if (pipe(end) < 0)
	{
		perror("pipe");
		close(cmd->in);
		return (0);
	}
	cmd->out = end[1];
	cmd->read_out = end[0];
	return (1);
}

static int	ft_open_outfile(int argc, char **argv, t_cmd *cmd)
{
	int	in;

	while (cmd->next)
	{
		in = cmd->read_out;
		cmd = cmd->next;
	}
	cmd->in = in;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		cmd->out = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
	else
		cmd->out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out < 0)
	{
		perror(argv[argc - 1]);
		close(cmd->in);
		return (0);
	}
	return (1);
}

int	ft_add_file(int i, int argc, char **argv, t_cmd *cmd)
{
	int	success;

	if (i == 2)
		success = ft_open_infile(argv, cmd);
	else if (i < argc - 2)
		success = ft_open_pipe(cmd);
	else
		success = ft_open_outfile(argc, argv, cmd);
	if (!success)
	{
		while (cmd->next)
			cmd = cmd->next;
		ft_free_array(cmd->args);
	}
	return (success);
}
