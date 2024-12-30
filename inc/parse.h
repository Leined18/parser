#ifndef PARSE_H
# define PARSE_H

# include "input.h"
# include "libft.h"
# include "mt.h"

// funtions to use
t_mt	*parse_input(const char *input);
int		ft_execute_list(t_mt *head, void *p, int (*proccess_node)(t_mt *,
				void *));
#endif // PARSE_H