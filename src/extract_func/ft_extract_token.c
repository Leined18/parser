/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:08:56 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/13 09:10:35 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_extract_token(char *str, int *i, char *allow, int (*funtion)(int))
{
	int	start;

	if (!i || !str)
		return (NULL);
	start = *i;
	while (funtion(str[*i]) || (ft_strchr(allow, str[*i]) && str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
