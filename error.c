/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <yel-mens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:44:58 by yel-mens          #+#    #+#             */
/*   Updated: 2025/04/22 14:29:16 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_free_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
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
			ft_free_array(cmd->args);
		if (cmd->in >= 0)
			close(cmd->in);
		if (cmd->out >= 0)
			close(cmd->out);
		if (next_cmd && next_cmd->in < 0)
			close(cmd->read_out);
		free(cmd);
		cmd = NULL;
		cmd = next_cmd;
	}
	ft_free_array(array);
	return (NULL);
}
