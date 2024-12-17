/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:34:47 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/17 17:31:17 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	**path;
	char	*args[3];
	char	*cmd;
	char	*arg;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = ft_split(envp[i] + 5, ':');
		i++;
	}
	args[0] = argv[1];
	args[1] = argv[2];
	args[2] = NULL;
	arg = NULL;
	i = 0;
	while (path[i])
	{
		arg = ft_strjoin("/", args[0]);
		cmd = ft_strjoin(path[i], arg);
		free(arg);
		if (access(cmd, X_OK) == 0)
		{
			int id = fork();
			if (id == 0)
				execve(cmd, args, envp);
		}
		free(cmd);
		i++;
	}
	for (int j=0; path[j]; j++)
		free(path[j]);
	free(path);
}
