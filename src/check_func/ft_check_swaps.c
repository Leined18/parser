/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_swaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:06:11 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/12 13:39:09 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	is_cmd_quotes_parentesis(t_mt *cur)
{
	if (cur && (ft_mtcheck_state(cur, COMMAND)
			|| ft_mtcheck_state(cur, SINGLE_QUOTE)
			|| ft_mtcheck_state(cur, DOUBLE_QUOTE)
			|| ft_mtcheck_state(cur, PARENTESIS)))
		return (1);
	return (0);
}

/*
It swaps the positions of the redirections and the commands if the command
is on the left side of the IN redirections. 
*/
void	ft_check_swaps(t_mt **token)
{
	t_mt	*cur;
	int		prev;

	if (!token || !*token)
		return ;
	prev = 0;
	cur = *token;
	while (cur)
	{
		if (ft_mtcheck_state(cur, PARENTESIS) && !cur->values.swap_checked)
		{
			ft_check_swaps(&cur->aux);
			cur->values.swap_checked = TRUE;
		}
		else if (is_cmd_quotes_parentesis(cur))
			prev = is_cmd_quotes_parentesis(cur->vect[LEFT]);
		else if (!ft_mtcheck_key(cur, "<") || !ft_mtcheck_key(cur, "<<"))
		{
			if (is_cmd_quotes_parentesis(cur->vect[LEFT]) && !prev)
				ft_mtexchange_dir(token, cur, LEFT);
		}
		cur = cur->vect[RIGHT];
	}
	check_follow_commands(token);
	check_follow_redout(token);
}
