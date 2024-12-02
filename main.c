/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:12:30 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/02 13:36:02 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_mt	*create_tree(char *name_root, int argc, ...)
{
	t_mt	*root;
	t_mt	*node;
	va_list	args;

	va_start(args, argc);
	root = ft_mtnew(name_root, NULL, NONE);
	while (argc--)
	{
		node = va_arg(args, t_mt *);
		ft_mtadd_child(root, node);
	}
	va_end(args);
	return (root);
}

t_hash_table	*parser(char *input)
{
	t_hash_table	*ptable;
	t_mt			*list;

	if (!input)
		return (NULL);
	ptable = ft_mthash_new_table(3, "parser");
	if (!ptable)
		return (NULL);
	list = tokenize(input);
	ptable->methods.add_child(ptable, "input", list);
	return (ptable);
}

int	main(void)
{
	t_hash_table	*ptable;
	char			*input;

	input = get_next_line(0);
    input[ft_strlen(input) - 1] = '\0';
	ptable = parser(input);
    free(input);
	if (!ptable)
		return (1);
	ptable->methods.print(ptable);
	ptable->methods.free_table(ptable);
	return (0);
}
