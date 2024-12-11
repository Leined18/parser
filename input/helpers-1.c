/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:47:38 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/11 10:55:09 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * is_quoted - Verifica si el caracter es una comilla simple o doble
 * @c: El caracter a verificar
 *
 * Return: 1 si es comilla, 0 si no lo es.
 */
int	is_quoted(char c)
{
	return (c == '\'' || c == '"');
}

/**
 * is_operator - Verifica si el caracter es un operador válido
 * @c: El caracter a verificar
 *
 * Return: 1 si es un operador, 0 si no lo es.
 */
int	is_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '!');
}

/**
 * is_redirection - Verifica si el caracter es un operador de redirección
 * @c: El caracter a verificar
 *
 * Return: 1 si es un operador de redirección, 0 si no lo es.
 */

int	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

/**
 * has_higher_precedence
	- Verifica si el primer operador tiene mayor precedencia
 * que el segundo.
 * @op1: El primer operador
 * @op2: El segundo operador
 *
 * Return: TRUE si op1 tiene mayor precedencia, FALSE si no.
 */
int	has_higher_precedence(char *op1, char *op2)
{
	if (!op1 || !op2)
		return (FALSE);
	// Para extender, podemos agregar un sistema de precedencia
	if (is_operator(op1[0]) && is_operator(op2[0]))
		return (TRUE);
	return (FALSE);
}

/**
 * is_whitespace - Verifica si el caracter es un espacio en blanco
 * @c: El caracter a verificar
 *
 * Return: 1 si es espacio en blanco, 0 si no lo es.
 */
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_asignation(char c)
{
	return (c == '=');
}

int	is_parentesis(char c)
{
	return (c == '(' || c == ')');
}
