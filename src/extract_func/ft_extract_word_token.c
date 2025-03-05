/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_word_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:10:22 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/05 11:00:04 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * ft_extract_word_token
	- Extrae un token de palabra (sin comillas ni operadores).
 */
char	*ft_extract_word_token(char *str, int *i, char *disallow)
{
	int		start;
	char	*token;
	t_mt	*add;

	if (!i || !str)
		return (NULL);
	start = *i;
	while ((((ft_isascii(str[*i]) && ft_isalnum(str[*i]))
				|| !ft_strchr(disallow, str[*i])) && str[*i]))
		(*i)++;
	add = NULL;
	if (str[*i] == '=')
	{
		(*i)++;
		if (str[*i])
		{
			ft_process_token(str, i, &add, ft_transition(START, str[*i]));
			ft_mtclear(&add);
		}
	}
	token = ft_substr(str, start, *i - start);
	return (token);
}
