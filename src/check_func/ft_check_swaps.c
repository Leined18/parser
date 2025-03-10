/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_swaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:06:11 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/10 11:43:02 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	check_prev_cmd(t_mt *cur)
{
	if (cur->vect[LEFT] && ft_mtcheck_state(cur->vect[LEFT], COMMAND))
		return (1);
	return (0);
}

/*
It swaps the positions of the redirections and the commands if the command
is on the left side of the redirections. 
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
		if (ft_mtcheck_state(cur, COMMAND))
			prev = check_prev_cmd(cur);
		else if (!ft_mtcheck_key(cur, "<") || !ft_mtcheck_key(cur, "<<"))
		{
			if (cur->vect[LEFT]
				&& (ft_mtcheck_state(cur->vect[LEFT], COMMAND)
					|| ft_mtcheck_state(cur->vect[LEFT], PARENTESIS)) && !prev)
			{
				ft_mtexchange_dir(token, cur, LEFT);
				prev = 0;
			}
		}
		cur = cur->vect[RIGHT];
	}
	check_follow_commands(token);
	check_follow_redout(token); 
}
