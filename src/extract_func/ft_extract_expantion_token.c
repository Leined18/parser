/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_expantion_token.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:34:49 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/30 12:08:09 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*ft_extract_expantion_token(char *str, int *i)
{
	char	*token;
	char	*dup;

	if (!i || !str)
		return (NULL);
	if (ft_strchr("$", str[*i]))
		*i += 1;
	if (ft_strchr("(", str[*i]))
	{
		token = ft_extract_parentheses_token(str, i);
		dup = ft_strdup("$");
		return (ft_strjoin_free(&dup, &token));
	}
	token = ft_extract_word_token(str, i);
	dup = ft_strdup("$");
	return (ft_strjoin_free(&dup, &token));
}
