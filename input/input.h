#ifndef INPUT_H
# define INPUT_H

# include "memtrack.h"

int	parser(char *input);
int	tokenize(char *str, t_mt **list);

#endif // INPUT_H