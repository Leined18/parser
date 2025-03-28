/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:34:20 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/28 10:16:34 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_is_pipe_arg(char *p)
{
	char	*tmp;
	int		i;

	if (ft_strchr(p, '|'))
	{
		tmp = ft_strchr(p, '|');
		i = 1;
		while (tmp[i] && ft_strchr("\t\v\n", tmp[i]))
			i++;
		if (ft_isascii(tmp[i]) && tmp[i])
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	ft_is_open(char *p)
{
	if (!p)
		return (0);
	if (!ft_check_is_close(p, '(', ')')
		|| !ft_check_is_close(p, '{', '}')
		|| !ft_check_is_close_quote(p, '\'')
		|| !ft_check_is_close_quote(p, '\"')
		|| !ft_is_pipe_arg(p))
		return (1);
	return (0);
}

int	ft_extend(char **input)
{
	char	*add;
	char	*ptr;

	if (!input || !*input)
		return (0);
	ptr = *input;
	if (!ft_is_open(ptr))
		return (1);
	while (ft_is_open(ptr))
	{
		add = advanced_readline("> ");
		if (!add && g_sig_received != SIGINT)
			return (ft_printf(SYNTAX_ERROR3, ptr), -1);
		else if (!add && g_sig_received == SIGINT)
			return (-2);
		ptr = ft_straddc(ptr, '\n');
		ptr = ft_strjoin_free(&ptr, &add, 1);
		if (!ptr)
			return (0);
		*input = ptr;
	}
	return (*input = ptr, 1);
}
