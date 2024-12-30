/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:38:35 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/30 12:56:58 by danpalac         ###   ########.fr       */
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
	current = current->vect.right;
	while (current != head)
	{
		if (current->values.state != END)
			return (0);
		current = current->vect.right;
	}
	return (1);
}

static void	make_circular(t_mt **list) // pone una conexcion circular
{
	(*list)->vect.left = ft_mtlast((*list));
	(*list)->vect.left->vect.right = (*list);
}

static void	unmake_circular(t_mt **list) // quita la conexion circular
{
	(*list)->vect.left->vect.right = NULL;
	(*list)->vect.left = NULL;
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
	make_circular(&head);
	while (!all_nodes_finished(head)) // exe until all end
	{
		if (current->values.state != END)
		{
			if (proccess_node(current, p))
				current->values.state = END;
		}
		current = current->vect.right;
	}
	unmake_circular(&head);
	return (1);
}
