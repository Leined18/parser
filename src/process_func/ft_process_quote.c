/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:32:01 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/03 09:11:21 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_process_quote(char *input, int *i, t_mt **list, t_pstate state)
{
	char	*token;

	if (!input || !i || !list)
		return (0);
	token = ft_extract_quoted_token(input, i);
	if (token)
	{
		ft_mtaddlast_right(list, ft_newnode(token, state));
		free(token);
	}
	return (1);
}
