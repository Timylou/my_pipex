/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:14:53 by yel-mens          #+#    #+#             */
/*   Updated: 2024/12/17 11:19:27 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		str[i] = s1[i];
	i = 0;
	while (i < len_s2)
	{
		str[i + len_s1] = s2[i];
		i++;
	}
	str[len_s1 + len_s2] = 0;
	return (str);
}

static char	*ft_alloc(unsigned int start, size_t *len, size_t str_len)
{
	char	*sub_str;

	if ((size_t) start >= str_len)
		*len = 0;
	else if (start + *len > str_len)
		*len = str_len - start;
	sub_str = malloc(sizeof(char) * (*len + 1));
	if (!sub_str)
		return (NULL);
	return (sub_str);
}

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_str;

	if (!str)
		return (NULL);
	sub_str = ft_alloc(start, &len, ft_strlen(str));
	if (!sub_str)
		return (NULL);
	i = 0;
	while (i < len)
		sub_str[i++] = str[start++];
	sub_str[i] = 0;
	return (sub_str);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	if (!n)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
