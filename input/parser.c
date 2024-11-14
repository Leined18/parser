/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:53 by danpalac          #+#    #+#             */
/*   Updated: 2024/11/14 17:27:38 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include <string.h> // Para strcmp

t_nodetype	check_data_type(const char *data)
{
	if (strcmp(data, "|") == 0 || strcmp(data, ";") == 0 || strcmp(data,
			"\n") == 0)
		return (NODE_SEQUENCE);
	if (strcmp(data, "&") == 0)
		return (NODE_BACKGROUND);
	if (strcmp(data, "&&") == 0)
		return (NODE_AND);
	if (strcmp(data, "||") == 0)
		return (NODE_OR);
	if (strcmp(data, "()") == 0)
		return (NODE_GROUP);
	if (strcmp(data, "$()") == 0 || strcmp(data, "``") == 0)
		return (NODE_SUBSHELL);
	if (strcmp(data, ">") == 0 || strcmp(data, "<") == 0)
		return (NODE_REDIRECT);
	if (strcmp(data, ">>") == 0 || strcmp(data, "<<") == 0)
		return (NODE_REDIRECT);
	if (strcmp(data, "=") == 0)
		return (NODE_ASSIGNMENT);
	return (NODE_COMMAND);
}

int	put_priority(t_mt *input)
{
	if (!input)
		return (0);
	while (input)
	{
		input->n = check_data_type((const char *)input->data);
		input = input->next;
	}
	return (1);
}

int	is_sorted(t_mt *input)
{
	if (!input)
		return (0);
	while (input && input->next)
	{
		if (input->n > input->next->n)
			return (0);
		input = input->next;
	}
	return (1);
}

int	sort_by_priority(t_mt **input)
{
	t_mt	*tmp;
	t_mt	*b;

	tmp = *input;
	while (!is_sorted(tmp))
	{
		while (tmp && tmp->next)
		{
			if (tmp->n > tmp->next->n)
			{
				ft_mtpush(&tmp, &b);
				ft_mtpush(&b);
			}
			tmp = tmp->next;
		}
		tmp = *input;
	}
	return (1);
}

int	parser(t_mt **input)
{
	if (!input || !*input)
		return (0);
	if (!put_priority(*input))
		return (0);
	if (!sort_by_priority(input))
		return (0);
	return (1);
}
