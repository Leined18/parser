/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danpalac <danpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:01:35 by danpalac          #+#    #+#             */
/*   Updated: 2025/03/21 14:04:10 by danpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "input.h"
# include "libft.h"
# include "mt.h"
# include <readline/readline.h>

# define SYNTAX_ERROR "syntax error near unexpected token `%s'\n"
# define SYNTAX_ERROR2 "syntax error near unexpected token `newline'\n"
# define SYNTAX_ERROR3 "unexpected EOF while looking for matching `%s'\n"

t_mt	*ft_parse_input(const char *input);
char	*advanced_readline(const char *prompt);

#endif