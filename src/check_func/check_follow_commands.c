/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_follow_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:37:20 by mvidal-h          #+#    #+#             */
/*   Updated: 2025/03/12 13:38:28 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	is_cmd_quotes(t_mt *cur)
{
	if (cur && (ft_mtcheck_state(cur, COMMAND)
			|| ft_mtcheck_state(cur, SINGLE_QUOTE)
			|| ft_mtcheck_state(cur, DOUBLE_QUOTE)))
		return (1);
	return (0);
}

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
		if (is_cmd_quotes(cur) && is_cmd_quotes(cur->vect[RIGHT]))
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
