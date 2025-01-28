/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_is_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:13:34 by danpalac          #+#    #+#             */
/*   Updated: 2024/12/12 10:14:02 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"


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
