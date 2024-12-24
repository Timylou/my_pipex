/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <yel-mens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:37:11 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/24 19:15:04 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_cmd
{
	char			**args;
	int				in;
	int				out;
	int				read_out;
	struct s_cmd	*next;
}	t_cmd;

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

t_cmd	*ft_init_struct(int argc, char **argv, char **env);
int		ft_add_file(int i, int argc, char **argv, t_cmd *cmd);
int		ft_add_args(char *complete_cmd, char **path, t_cmd *cmd);
char	*ft_free_array(char **array);
t_cmd	*ft_free_struct(t_cmd *cmd, char **array);
int		here_doc(char *limiter, t_cmd *cmd, char **path);

#endif
