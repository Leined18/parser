/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_utils-1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:53:52 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/10 12:13:48 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	ft_find_token_length(char *str, int start, char *delim)
{
	int	len;

	len = 0;
	while (str[start + len] && !ft_strchr(delim, str[start + len]))
		len++;
	return (len);
}

char	*ft_extract_token(char *str, int *start, int *end, char *delim)
{
	int		len;
	char	*token;

	if (!str || !delim)
		return (NULL);
	len = ft_find_token_length(str, *start, delim);
	token = ft_substr(str, *start, len);
	*end += len;
	return (token);
}

int	ft_process_expansion(char *input, int *i, t_mt **list, e_pstate state)
{
	char *token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_token(input, i, 0, "\t\v\n ><|)");
	if (!token)
		return (0);
	if (ft_strchr("$", input[*i]))
		(*i)++;
	if (ft_strchr("()", token))
		return (ft_process_parentheses(input, i, list, "$()"));
	else
		ft_mtaddlast_right(list, ft_newnode(token, state));
	free(token);
	return (1);
}