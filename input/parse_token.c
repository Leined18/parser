/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:53 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/02 13:32:09 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	add_token(t_mt **tokens, char *token);
static char	*extract_quoted_token(char *str, int *i);
static char	*extract_operator_token(char *str, int *i);
static char	*extract_word_token(char *str, int *i);

/**
 * parse_token - Procesa un único token desde la posición actual de la cadena.
 * @str: Cadena de entrada.
 * @i: Posición actual en la cadena (se actualiza).
 * @tokens: Lista enlazada donde se agregan los tokens.
 */
void	parse_token(char *str, int *i, t_mt **tokens)
{
	char	*token;

	if (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	else if (str[*i] == '\'' || str[*i] == '"')
	{
		token = extract_quoted_token(str, i);
		add_token(tokens, token);
	}
	else if (str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
	{
		token = extract_operator_token(str, i);
		add_token(tokens, token);
	}
	else
	{
		token = extract_word_token(str, i);
		add_token(tokens, token);
	}
}

/**
 * add_token - Añade un nuevo token a la lista enlazada.
 */
static void	add_token(t_mt **head, char *token)
{
	t_mt	*new_node;

	new_node = ft_mtnew(token, token, STRING);
	if (!new_node)
		return ;
	ft_mtadd_back(head, new_node);
}

/**
 * extract_quoted_token - Extrae un token delimitado por comillas.
 */
static char	*extract_quoted_token(char *str, int *i)
{
	char	quote;
	int		start;

	quote = str[(*i)++];
	start = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
	// Saltar el cierre de la comilla
	return (ft_substr(str, start, *i - start - 1)); // Excluye las comillas
}

/**
 * extract_operator_token - Extrae un operador (|, >, <, >>, <<).
 */
static char	*extract_operator_token(char *str, int *i)
{
	int	start;

	start = *i;
	if (str[*i + 1] == str[*i]) // Detectar operadores dobles (>>, <<)
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

/**
 * extract_word_token - Extrae un token de palabra (sin comillas ni operadores).
 */
static char	*extract_word_token(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\''
		&& str[*i] != '"' && str[*i] != '|' && str[*i] != '>' && str[*i] != '<')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
