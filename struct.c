/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:46:25 by yel-mens          #+#    #+#             */
/*   Updated: 2025/04/23 13:04:48 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_get_path(char **env)
{
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path = ft_split(env[i] + 5, ':');
			return (path);
		}
		i++;
	}
	path = malloc(sizeof(char *));
	path[0] = NULL;
	return (path);
}

static t_cmd	*ft_add_struct(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->in = -1;
	new_cmd->out = -1;
	new_cmd->read_out = -1;
	new_cmd->next = NULL;
	return (new_cmd);
}

static int	ft_add_end(t_cmd *cmd)
{
	t_cmd	*new_cmd;

	if (!cmd)
		return (0);
	new_cmd = ft_add_struct();
	if (!new_cmd)
		return (0);
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = new_cmd;
	return (1);
}

static t_cmd	*ft_first_cmd(int argc, char **argv, char **path)
{
	t_cmd	*cmd;
	int		is_here_doc;

	is_here_doc = 0;
	if (!ft_strncmp(argv[1], "here_doc", 8))
		is_here_doc = 1;
	cmd = ft_add_struct();
	if (!cmd)
		return (NULL);
	else if (!ft_add_file(2, argc, argv, cmd))
		return (ft_free_struct(cmd, path));
	if (cmd->in < 0)
		return (cmd);
	ft_add_args(argv[2 + is_here_doc], path, cmd);
	if (is_here_doc)
	{
		if (!here_doc(argv[2], cmd, path))
			return (ft_free_struct(cmd, path));
	}
	return (cmd);
}

t_cmd	*ft_init_struct(int argc, char **argv, char **env)
{
	char	**path;
	t_cmd	*cmd;
	int		i;

	path = ft_get_path(env);
	if (!path)
		return (NULL);
	cmd = ft_first_cmd(argc, argv, path);
	if (!cmd)
		return (ft_free_struct(cmd, ft_split("useless str ...", ' ')));
	i = 3;
	while (i < argc - 1)
	{
		if (!ft_add_end(cmd))
			return (ft_free_struct(cmd, path));
		ft_add_args(argv[i], path, cmd);
		ft_add_file(i, argc, argv, cmd);
		i++;
	}
	ft_free_array(path);
	return (cmd);
}
