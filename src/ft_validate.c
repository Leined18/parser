/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:35:06 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/27 11:35:11 by danpalac         ###   ########.fr       */
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
	{
		if (!mt->aux)
			return (*(int *)p = 1, ft_printf(SYNTAX_ERROR, ")"), 1);
		if (ft_mtcheck_state(mt->vect[RIGHT], PARENTESIS))
			return (*(int *)p = 1, ft_printf(SYNTAX_ERROR, "("), 1);
		if (ft_mtcheck_state(mt->vect[LEFT], PARENTESIS))
			return (*(int *)p = 1, ft_printf(SYNTAX_ERROR, "()"), 1);
	}
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
