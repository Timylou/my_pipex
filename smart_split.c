/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:03:20 by yel-mens          #+#    #+#             */
/*   Updated: 2025/04/27 19:04:16 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	word_len(const char *s)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (s[len] && (quote || s[len] != ' '))
	{
		if (is_quote(s[len]) && !quote)
			quote = s[len];
		else if (s[len] == quote)
			quote = 0;
		len++;
	}
	return (len);
}

static int	count_words(const char *s)
{
	int		count;
	int		i;
	char	quote;

	count = 0;
	i = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '\0')
			break ;
		count++;
		while (s[i] && (quote || s[i] != ' '))
		{
			if (is_quote(s[i]) && !quote)
				quote = s[i];
			else if (s[i] == quote)
				quote = 0;
			i++;
		}
	}
	return (count);
}

static char	*malloc_word(const char *s, int len)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**smart_split(const char *s)
{
	char	**tab;
	int		words;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	words = count_words(s);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (!*s)
			break ;
		len = word_len(s);
		tab[i++] = malloc_word(s, len);
		s += len;
	}
	tab[i] = NULL;
	return (tab);
}
