/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:29:34 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/17 18:06:30 by yel-mens         ###   ########.fr       */
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
			path = ft_split(env[i] + 5, ':');
		i++;
	}
	return (path);
}

static char **ft_get_cmd(char *cmd, int fd)
{
	char	**args;

	args = malloc(sizeof(char *) * 3);
	if (!args)
		return (NULL);
	args[0] = cmd;

}

int	ft_exec_cmd(char *cmd, int fd, char **env)
{
	char	**path;

	path = ft_get_path(env);
	if (!path)
		return (0);
	
}
