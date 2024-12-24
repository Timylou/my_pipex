/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:44:58 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/24 13:34:54 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}

t_cmd	*ft_free_struct(t_cmd *cmd, char **array)
{
	t_cmd	*next_cmd;

	next_cmd = NULL;
	while (cmd)
	{
		next_cmd = cmd->next;
		if (cmd->args)
		{
			ft_free_array(cmd->args);
			close(cmd->in);
			close(cmd->out);
		}
		free(cmd);
		cmd = NULL;
		cmd = next_cmd;
	}
	ft_free_array(array);
	return (NULL);
}
