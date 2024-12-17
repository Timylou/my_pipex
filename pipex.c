/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:11:35 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/17 18:08:01 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	fd[2];

	if (argc != 5)
		return (EXIT_FAILURE);
	if (!ft_open_files(fd, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
