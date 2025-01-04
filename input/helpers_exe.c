/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:38:35 by danpalac          #+#    #+#             */
/*   Updated: 2025/01/04 22:19:39 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief checkea si todos los nodos tienen el estado END
 *
 * @param head
 * @return int
 */

static int	all_nodes_finished(t_mt *head)

{
	t_mt *current;

	current = head;
	if (!head)
		return (1);
	if (current->values.state != END)
		return (0);
	current = current->vect[RIGHT];
	while (current != head)
	{
		if (current->values.state != END)
			return (0);
		current = current->vect[RIGHT];
	}
	return (1);
}

static void	make_circular(t_mt **list) // pone una conexcion circular
{
	(*list)->vect[LEFT] = ft_mtlast((*list), RIGHT);
	(*list)->vect[LEFT]->vect[RIGHT] = (*list);
}

static void	unmake_circular(t_mt **list) // quita la conexion circular
{
	(*list)->vect[LEFT]->vect[RIGHT] = NULL;
	(*list)->vect[LEFT] = NULL;
}

static int	is_circular(t_mt *list)
{
	t_mt	*current;

	current = list;
	while (current->vect[RIGHT])
	{
		if (current->vect[RIGHT] == list)
			return (1);
		current = current->vect[RIGHT];
	}
	return (0);
}

/**
 * @brief funcion para uso modular, pasas una funcion,
	si devuelve 1 es que has terminado y marca estado END
 *
 * @param head la cabeza de la lista
 * @param proccess_node la funcion para procesar cada nodo
 */

int	ft_execute_list(t_mt *head, void *p, int (*proccess_node)(t_mt *, void *))
{
	t_mt	*current;
	int		i;

	current = head;
	if (!head)
		return (-1);
	i = 0;
	if (!p)
		return (ft_execute_list(head, &i, proccess_node));
	if (!is_circular(head))
		make_circular(&head);
	while (!all_nodes_finished(head)) // exe until all end
	{
		if (current->values.state != END)
		{
			if (proccess_node(current, p))
				current->values.state = END;
		}
		current = current->vect[RIGHT];
	}
	unmake_circular(&head);
	return (1);
}
