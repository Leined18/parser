/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:01:35 by danpalac          #+#    #+#             */
/*   Updated: 2025/02/27 09:31:02 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "input.h"
# include "libft.h"
# include "mt.h"

# define SYNTAX_ERROR "syntax error near unexpected token `%s'\n"

t_mt	*ft_parse_input(const char *input);

#endif