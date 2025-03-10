/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:02:24 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/10 10:05:04 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_validate_input(char *s)
{
	if (!s)
		return (0);
	if (ft_strchr("|)", s[0]))
		return (s[1] = 0, ft_printf(SYNTAX_ERROR, s), 0);
	return (1);
}

static int	ft_check(t_mt *mt, void *p)
{
	if (!mt || *(int *)p > 0)
		return (0);
	if (ft_mtcheck_state(mt, REDIRECTION))
		return (ft_check_redirections_mt(mt, (int *)p));
	else if (ft_mtcheck_state(mt, OPERATOR))
		return (ft_check_operators_mt(mt, (int *)p));
	else if (ft_mtcheck_state(mt, PARENTESIS))
		return (ft_check_parentesis_mt(mt, (int *)p));
	return (0);
}

int	ft_validate_list(t_mt *list)
{
	int	res;
	int	error;

	error = 0;
	res = ft_mtfold(list, &error, ft_check);
	return (res == 0);
}
