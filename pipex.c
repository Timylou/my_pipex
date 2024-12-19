/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:11:35 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/19 14:11:57 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	end[2];
	int	id;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (pipe(end) == -1)
		return (EXIT_FAILURE);
	id = fork();
	if (!id)
		ft_child_process(end, argv, env);
	else
		ft_parent_process(end, argv, env);
	return (EXIT_SUCCESS);
}
