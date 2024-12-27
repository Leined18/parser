/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/27 08:49:07 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * parser - Main parser function to create a hash table and organize input
 * @input: The input string
 * Returns: A hash table with the parsed data
 */

void	print_state(t_mt *list, void *a)
{
	(void)a;
	printf("key: %s\n", (char *)list->key);
	printf("Data: %s\n", (char *)list->data);
	printf("State: %d\n", list->values.state);
}

int	all_nodes_finished(t_mt *head)
{
	t_mt	*current;

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

int	node_is_finished(t_mt *node)
{
	if (!node)
		return (-1);
	if (node->values.state == END)
		return (1);
	return (0);
}

void	execute_circular_list(t_mt *head, int (*proccess_node)(t_mt *))
{
	t_mt	*current;

	current = head;
	if (!head)
		return ;
	while (1)
	{
		// Procesar solo nodos que no están en estado END
		if (current->values.state != END)
		{
			if (proccess_node(current))
				current->values.state = END;
		}
		// Avanzar al siguiente nodo
		current = current->vect.right;
		// Salir si todos los nodos están en estado END
		if (all_nodes_finished(head))
			break ;
	}
}

int	f(t_mt *list)
{
	if (!list)
		return (-1);
	printf("key: %s\n", (char *)list->key);
	printf("Data: %s\n", (char *)list->data);
	printf("State: %d\n", list->values.state);
	list->values.state = END;
	return (1);
}

int	main(void)
{
	char	*input;
	t_mt	*list;

	input = get_next_line(0);
	input[ft_strlen(input) - 1] = '\0';
	list = NULL;
	list = parse_input(input);
	if (!list)
	{
		free(input);
		ft_error("Error\n", 1);
		return (1);
	}
	list->vect.left = ft_mtlast(list);
	list->vect.left->vect.right = list;
	execute_circular_list(list, f);
	list->vect.left->vect.right = NULL;
	list->vect.left = NULL;
	ft_mtclear(&list);
	free(input);
	ft_successful("Success\n", 1);
	return (0);
}

/* t_hash_table	*parser(char *input)
{
	t_hash_table	*ptable;
	t_mt			*tree;

	if (!input)
		return (NULL);
	ptable = ft_mthash_new_table(3, "parser");
	if (!ptable)
		return (NULL);
	tree = tokenize(input);
	parse_input(input);
	if (!tree)
	{
		ft_mthash_table_free((void **)&ptable);
		return (NULL);
	}
	ptable->methods.add_child(ptable, "tree", tree);
	return (ptable);
} */