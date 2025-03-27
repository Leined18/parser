/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_expantion_token.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:34:49 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/27 11:05:33 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*ft_extract_expantion_token(char *str, int *i)
{
	char	*token;
	char	*dup;

	if (!i || !str)
		return (NULL);
	if (str[*i] == '$')
		*i += 1;
	if (str[*i] == '(')
	{
		token = ft_extract_parentheses_token(str, i);
		dup = ft_strdup("$");
		return (ft_strjoin_free(&dup, &token, 1));
	}
	if (str[*i] == '?')
	{
		token = ft_strdup("?");
		(*i)++;
	}
	else
		token = ft_extract_token(str, i, "_", ft_isalnum);
	dup = ft_strdup("$");
	return (ft_strjoin_free(&dup, &token, 1));
}
