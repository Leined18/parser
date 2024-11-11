#ifndef NODE_H
# define NODE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_mt
{
	void		*data;
	struct s_mt	*next;
}				t_mt;

t_mt	*ft_mtnew(void *data);

#endif // LIST_H