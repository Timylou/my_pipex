/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <yel-mens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:10:08 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/24 15:42:04 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_access(char *cmd_name, char **path)
{
	int		i;
	char	*arg;
	char	*cmd_path;

	i = 0;
	while (path[i])
	{
		arg = ft_strjoin("/", cmd_name);
		cmd_path = ft_strjoin(path[i], arg);
		free(arg);
		if (!access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static int	ft_fill_args(char **splited_name, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (splited_name[++i])
	{
		cmd->args[i] = ft_strjoin(splited_name[i], "");
		if (!(cmd->args[i]))
		{
			while (i-- >= -1)
				free(cmd->args[i]);
			free(cmd->args);
			cmd->args = NULL;
			ft_free_array(splited_name);
			return (0);
		}
	}
	cmd->args[i] = NULL;
	ft_free_array(splited_name);
	return (1);
}

int	ft_add_args(char *complete_cmd, char **path, t_cmd *cmd)
{
	char	**splited_name;
	int		i;

	while (cmd->next)
		cmd = cmd->next;
	splited_name = ft_split(complete_cmd, ' ');
	i = 0;
	while (splited_name[i])
		i++;
	cmd->args = malloc(sizeof(char *) * (i + 1));
	cmd->args[0] = ft_access(splited_name[0], path);
	if (!cmd->args[0])
	{
		free(cmd->args);
		cmd->args = NULL;
		return (0);
	}
	if (!ft_fill_args(splited_name, cmd))
		return (0);
	return (1);
}
