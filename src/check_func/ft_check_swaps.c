/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_swaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:06:11 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/06 18:03:10 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	need_redirect_swap(t_mt *tokens)
{
	if (!ft_mtcheck_key(tokens->vect[RIGHT], "<"))
		return (1);
	if (!ft_mtcheck_key(tokens->vect[RIGHT], "<<"))
		return (1);
	return (0);
}

/*
It checks if node has aux list and returns a pointer to it disconnecting 
the whole aux list from the node.
*/
t_mt	*ft_disconnect_aux(t_mt **node)
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
void	ft_mtlink_last_aux(t_mt **cur, t_mt *aux_substracted)
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
void	check_follow_commands(t_mt **token)
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

/*
It swaps the positions of the redirections and the commands if the command
is on the left side of the redirections. 
*/
void	ft_check_swaps(t_mt **token)
{
	t_mt	*cur;

	if (!token || !*token)
		return ;
	if ((ft_mtcheck_state(*token, COMMAND)
			|| ft_mtcheck_state(*token, PARENTESIS))
		&& need_redirect_swap(*token))
		ft_mtswap(token, RIGHT);
	cur = *token;
	while (cur)
	{
		if (ft_mtcheck_state(cur, COMMAND))
		{
			if (cur->vect[LEFT] && ft_mtcheck_state(cur->vect[LEFT], COMMAND))
			cur = cur->vect[RIGHT];
		}
		else if (!ft_mtcheck_key(cur, "<") || !ft_mtcheck_key(cur, "<<"))
		{
			if (cur->vect[LEFT] && ft_mtcheck_state(cur->vect[LEFT], COMMAND))
				ft_mtexchange(token, cur, LEFT);
		}
		if (cur)
			cur = cur->vect[RIGHT];
	}
	check_follow_commands(token);
}
