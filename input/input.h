#ifndef INPUT_H
# define INPUT_H

# include "config.h"
# include "minishell.h"
# include "shell.h"

int	parse_arguments(t_memory *mem, int ac, char **av, char **ev);

#endif // INPUT_H