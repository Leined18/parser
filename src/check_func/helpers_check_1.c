/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_check_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:11:34 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/27 11:03:44 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*ft_strjoin_free(char **s1, char **s2, int free_s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(*s1, *s2);
	free_null((void **)s1);
	if (free_s2)
		free_null((void **)s2);
	return (result);
}

int	ft_check_is_close(char *input, char open, char close)
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

int	ft_check_is_close_quote(char *input, char quote)
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

int	ft_check_operators_mt(t_mt *op, int *error)
{
	t_mt	*current;

	if (!op)
		return (1);
	current = op;
	if (!current->vect[LEFT])
	{
		ft_printf(SYNTAX_ERROR, (char *)current->data);
		return (*error = 1, 1);
	}
	if (ft_mtcheck_state(current->vect[RIGHT], OPERATOR))
	{
		ft_printf(SYNTAX_ERROR, (char *)current->vect[RIGHT]->data);
		return (*error = 1, 1);
	}
	return (0);
}

int	ft_check_redirections_mt(t_mt *op, int *error)
{
	char	*s;

	if (!op)
		return (1);
	s = NULL;
	if (!op->vect[RIGHT])
		return (*error = 1, ft_printf(SYNTAX_ERROR, "newline"), 1);
	if (!ft_mtcheck_state(op->vect[RIGHT], WORD))
	{
		if (ft_mtcheck_state(op->vect[RIGHT], PARENTESIS))
			return (0);
		else if (op->vect[RIGHT])
			s = ((char *)op->vect[RIGHT]->data);
		return (*error = 1, ft_printf(SYNTAX_ERROR, s, 1));
	}
	return (0);
}
