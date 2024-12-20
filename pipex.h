/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:37:11 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/21 14:56:57 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

/* * * * * *
 *	utils  *
 * * * * * */

char	**ft_split(char const *str, char sep);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

/* * * * * *
 *	pipex  *
 * * * * * */

void	ft_child_process(int i, char **argv, char **env);
void	ft_child_file(int end[2], int i, char **argv);
void	ft_parent_process(int i, char **argv, char **env);
void	ft_parent_file(int end[2], int i, int argc, char **argv);
char	*ft_get_cmd_path(char *cmd, char **env);
char	*ft_free_array(char **array);

#endif
