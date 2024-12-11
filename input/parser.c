/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:19:37 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/11 16:41:18 by danpalac         ###   ########.fr       */
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

int	check_is_close(char **input, char open, char close)
{
	int	open_count;
	int	close_count;
	int	i;

	if (!input || !*input)
		return (-1);
	open_count = 0;
	close_count = 0;
	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == open)
			open_count++;
		else if ((*input)[i] == close)
			close_count++;
		i++;
	}
	if (open == close)
		return (open_count % 2 != 0);
	return (open_count == close_count);
}

int	extend_until_close(char **input)
{
	char	*add;
	char	*ptr;

	if (!input || !*input)
		return (0);
	ptr = *input;
	while (!check_is_close(&ptr, '(', ')') || !check_is_close(&ptr, '{', '}')
		|| check_is_close(&ptr, '\'', '\'') || check_is_close(&ptr, '\"',
			'\"'))
	{
		ft_printf("> ");
		add = get_next_line(0);
		if (!add)
			return (0);
		add[ft_strlen(add) - 1] = '\0';
		ptr = ft_strjoin_free(&ptr, &add);
		if (!ptr)
			return (0); // Si hubo un error al concatenar, retornamos error
		*input = ptr;   // Actualizamos el input con el nuevo contenido
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
	tokens = tokenize(input_new, &i);
	free(input_new);
	return (tokens);
}
