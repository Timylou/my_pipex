/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:23:12 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/19 14:15:29 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_free_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (NULL);
}

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
	return (NULL);
}

static char	*ft_get_valid_path(char **args, char **path)
{
	char	*cmd;
	char	*arg;
	int		i;

	arg = NULL;
	cmd = NULL;
	i = 0;
	while (path[i])
	{
		arg = ft_strjoin("/", args[0]);
		cmd = ft_strjoin(path[i], arg);
		free(arg);
		if (!access(cmd, X_OK))
		{
			free(cmd);
			return (ft_substr(path[i], 0, ft_strlen(path[i])));
		}
		free(cmd);
		i++;
	}
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char **env)
{
	char	**path;
	char	**args;
	char	*path_cmd;

	path = ft_get_path(env);
	if (!path)
		return (NULL);
	args = ft_split(cmd, ' ');
	if (!args)
		return (ft_free_array(path));
	path_cmd = ft_get_valid_path(args, path);
	ft_free_array(path);
	ft_free_array(args);
	return (path_cmd);
}
