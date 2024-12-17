/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:11:54 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/17 11:14:34 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_countwords(char const *str, char sep)
{
	int	i;
	int	nb_words;
	int	is_word;

	is_word = 1;
	nb_words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
		{
			is_word = 0;
			i++;
		}
		while (str[i] && str[i] != sep)
		{
			is_word = 1;
			i++;
		}
		if (is_word)
			nb_words++;
	}
	return (nb_words);
}

static int	ft_goto_nextword(char const *str, char sep, int cur_pos)
{
	while (str[cur_pos] && str[cur_pos] == sep)
		cur_pos++;
	return (cur_pos);
}

static int	ft_goto_endword(char const *str, char sep, int cur_pos)
{
	while (str[cur_pos] && str[cur_pos] != sep)
		cur_pos++;
	return (cur_pos);
}

static char	**ft_gosplit(const char *str, char sep, char **split, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	cur_pos;

	cur_pos = 0;
	i = 0;
	while (i < len)
	{
		i = ft_goto_nextword(str, sep, i);
		j = ft_goto_endword(str, sep, i);
		if (i != len)
		{
			split[cur_pos++] = ft_substr(str, i, j - i);
			if (!split[cur_pos - 1])
			{
				while (cur_pos > 0)
					free(split[--cur_pos]);
				free(split);
				return (NULL);
			}
		}
		i = j;
	}
	split[cur_pos] = NULL;
	return (split);
}

char	**ft_split(char const *str, char sep)
{
	size_t	str_len;
	size_t	nb_words;
	char	**splited;

	if (!str)
		return (NULL);
	nb_words = ft_countwords(str, sep);
	splited = malloc(sizeof(char *) * (nb_words + 1));
	if (!splited)
		return (NULL);
	str_len = ft_strlen(str);
	splited = ft_gosplit(str, sep, splited, str_len);
	return (splited);
}
