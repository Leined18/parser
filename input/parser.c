/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/12 12:14:01 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	extend_until_close(char **input)
{
	char	*add;
	char	*ptr;

	if (!input || !*input)
		return (0);
	if ((check_is_close(*input, '(', 0) && check_is_close(*input, '{', 0))
		&& (check_is_close_quote(*input, '\'') && check_is_close_quote(*input,
				'\"')))
		return (1);
	ptr = *input;
	while (!check_is_close(ptr, '(', ')') || !check_is_close(ptr, '{', '}')
		|| !check_is_close_quote(ptr, '\'') || !check_is_close_quote(ptr, '\"'))
	{
		ft_printf("> ");
		add = get_next_line(0);
		if (!add)
			return (0);
		add[ft_strlen(add) - 1] = '\0';
		ptr = ft_strjoin_free(&ptr, &add);
		if (!ptr)
			return (0);
		*input = ptr; // Actualizamos el input con el nuevo contenido
	}
	return (1); // Paréntesis balanceados
}

int	validate_list(t_mt *list)
{
	t_mt	*current;

	if (!list)
		return (0); // Lista vacía
	current = list;
	while (current)
	{
		if (current->values.state == REDIRECTION)
			return (check_redirections_mt(current)); // checkeo Redirecciones
		if (current->values.state == OPERATOR)
			return (check_operators_mt(current)); // checkeo Operadores
		if (current->values.state == PARENTESIS)
		{ // Paréntesis
			if (!current->children)
				ft_printf("syntax error near unexpected token `)'\n");
			if (!validate_list(current->children))
				return (0); // Paréntesis no balanceados
		}
		current = current->right;
	}
	return (1); // Paréntesis balanceados
}

t_mt	*parse_input(const char *input)
{
	t_mt	*tokens;
	int		i;
	char	*input_new;

	i = 0;
	input_new = ft_strdup(input);
	if (!extend_until_close((char **)&input_new))
		return (NULL);
	tokens = tokenize(input_new, &i); // Tokenizamos el input en nodos
	if (!tokens)
	{
		free(input_new);
		return (NULL);
	}
	if (!validate_list(tokens)) // Validamos la lista de tokens
	{
		ft_mtclear(&tokens);
		tokens = NULL;
	}
	free(input_new);
	return (tokens);
}
