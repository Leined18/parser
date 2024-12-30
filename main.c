/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/30 12:24:57 by danpalac         ###   ########.fr       */
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

int	process_0_priority(t_mt *list, void *i, int (*func)(t_mt *, void *))
// funcion de ejemplo
{
	if (list->aux)
		func(list->aux, i);
	return (1);
}

int	pred(t_mt *lst, void *p)
{
	if (!lst)
		return (-1);
	if (lst->values.priority == *(int *)p && lst->values.state != END)
		return (1);
	return (0);
}

int	exe(t_mt *list, void *i)
{
	int	j;

	if (!list)
		return (-1);
	j = 0;
	if (!ft_mtsearch(list, i, pred))
		*(int *)i += 1;
	if (list->values.priority == 0 && *(int *)i == 0) // parentesis
		return (ft_execute_list(list->aux, &j, exe));
	else if (list->values.priority == 1 && *(int *)i == 1) // logic op
		return (1);
	else if (list->values.priority == 2 && *(int *)i == 2) // redirections
		return (1);
	else if (list->values.priority == 3 && *(int *)i == 3) // operators
		return (1);
	else if (list->values.priority == 4 && *(int *)i == 4) // words
	{
		printf("key: %s\n", (char *)list->key);
		printf("Data: %s\n", (char *)list->data);
		printf("State: %d\n", list->values.state);
		printf("priority: %d\n", list->values.priority);
		return (1);
	}
	else if (list->values.priority == 5 && *(int *)i == 5) // assignaments
		return (1);
	return (0);
}

int	main(void)
{
	char	*input;
	t_mt	*list;
	int		i;

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
	printf("\n");
	i = 0;
	ft_set_priority(list, NULL, set_node_priority);
	ft_execute_list(list, &i, exe);
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