/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_swaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:06:11 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/10 11:09:02 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
It checks if node has aux list and returns a pointer to it disconnecting 
the whole aux list from the node.
*/
static t_mt	*ft_disconnect_aux(t_mt **node)
{
	t_mt	*aux;

	if (!node || !*node || !(*node)->aux)
		return (NULL);
	aux = (*node)->aux;
	(*node)->aux = NULL;
	return (aux);
}

/*
It links the list aux_substracted to the last node of the auxiliary list
 of cur.
*/
static void	ft_mtlink_last_aux(t_mt **cur, t_mt *aux_substracted)
{
	t_mt	*next;

	if (!cur || !*cur || !aux_substracted)
		return ;
	if (!(*cur)->aux)
		(*cur)->aux = aux_substracted;
	else
	{
		next = (*cur)->aux;
		while (next->vect[RIGHT])
			next = next->vect[RIGHT];
		next->vect[RIGHT] = aux_substracted;
	}
}

/*
It checks if there are commands that are followed by other commands.
Substracts the second one from the main list and links it to the
auxiliary list of the first one. If the subsctracted command has an
auxiliary list, it links it to the last node of the auxiliary list of the
first command.
In this way it fails if the firts command is followed by
a non aceptable argument for first command or print everything as arguments
if firts command is echo.
*/
static void	check_follow_commands(t_mt **token)
{
	t_mt	*cur;
	t_mt	*substracted;
	t_mt	*aux_substracted;

	if (!token || !*token)
		return ;
	cur = *token;
	while (cur)
	{
		if (ft_mtcheck_state(cur, COMMAND) && cur->vect[RIGHT]
			&& ft_mtcheck_state(cur->vect[RIGHT], COMMAND))
		{
			substracted = ft_mtsub(&cur, cur->vect[RIGHT]);
			aux_substracted = ft_disconnect_aux(&substracted);
			ft_mtpush_last(&cur->aux, &substracted, RIGHT);
			if (aux_substracted)
				ft_mtlink_last_aux(&cur, aux_substracted);
		}
		else
			cur = cur->vect[RIGHT];
	}
}

int	check_prev_cmd(t_mt *cur)
{
	if (cur->vect[LEFT] && ft_mtcheck_state(cur->vect[LEFT], COMMAND))
		return (1);
	return (0);
}

int	is_redout(t_mt *cur)
{
	if (!cur)
		return (0);
	if (!ft_mtcheck_key(cur, ">") || !ft_mtcheck_key(cur, ">>"))
		return (1);
	return (0);
}


static void check_follow_redout(t_mt **token) //EN PROCESO
{
	t_mt	*cur;
	t_mt	*last;
	t_mt	*first;

	if (!token || !*token)
		return ;
	cur = *token;
	first = NULL;
	last = NULL;
	while (cur && !last)
	{
		if (is_redout(cur))
		{
			if (!first)
				first = cur;
			if (!is_redout(cur->vect[RIGHT]))
				last = cur;
		}
		cur = cur->vect[RIGHT];
	}
	if (first)
		ft_printf("first: %s\n", first->key);
	if (last)
		ft_printf("last: %s\n", last->key);
	if (first && last && first != last)
		ft_mtexchange_nodes(token, first, last);
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
