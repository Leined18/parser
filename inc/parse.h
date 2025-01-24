#ifndef PARSE_H
# define PARSE_H

# include "input.h"
# include "libft.h"
# include "mt.h"

// funtions to use
t_mt	*ft_parse_input(const char *input);
void	print_elements(t_mt *node, int depth);
#endif // PARSE_H