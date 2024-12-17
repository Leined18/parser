/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_parse_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:11:34 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/17 17:08:37 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*ft_strjoin_free(char **s1, char **s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(*s1, *s2);
	free_null((void **)s1);
	free_null((void **)s2);
	return (result);
}

int	check_is_close(char *input, char open, char close)
{
	int	open_count;
	int	close_count;
	int	i;

	if (!input)
		return (-1);
	open_count = 0;
	close_count = 0;
	i = 0;
	while ((input)[i])
	{
		if ((input)[i] == open)
			open_count++;
		else if ((input)[i] == close)
			close_count++;
		i++;
	}
	return (open_count == close_count);
}
int	check_is_close_quote(char *input, char quote)
{
	int	is_open;
	int	in_single_quotes;
	int	in_double_quotes;
	int	i;

	is_open = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		if (input[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (input[i] == quote && ((quote == '\'' && !in_double_quotes)
					|| (quote == '\"' && !in_single_quotes)))
			is_open = !is_open;
		i++;
	}
	return (is_open == 0);
}

int	check_operators_mt(t_mt *op)
{
	t_mt	*current;

	if (!op)
		return (1);
	current = op;
	if (!current->left || !current->right)
	{
		ft_printf("syntax error near unexpected token `%s'\n",
			(char *)current->data);
		return (1);
	}
	return (0);
}

int	check_redirections_mt(t_mt *op)
{
	t_mt	*current;

	if (!op)
		return (1);
	current = op;
	if (!current->right || !current->left)
	{
		if (current->right && current->right->values.state != WORD)
			ft_printf("syntax error near unexpected token `%s'\n",
				(char *)current->right->data);
		else if (current->left && current->left->values.state != WORD)
			ft_printf("syntax error near unexpected token `%s'\n",
				(char *)current->left->data);
		else if (!current->right)
			ft_printf("syntax error near unexpected token `newline'\n");
		else
			return (0);
		return (1);
	}
	return (0);
}
