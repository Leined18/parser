#ifndef INPUT_H
# define INPUT_H

# include "memtrack.h"

typedef enum e_nodetype
{
	NODE_GROUP,      // Agrupación de comandos '()'
	NODE_SUBSHELL,   // Subshells '$( ... )' o backticks `` `...` ``
	NODE_REDIRECT,   // Redirección '>', '<', '>>', '<<'
	NODE_BACKGROUND, // Ejecución en segundo plano '&'
	NODE_AND,        // Operador lógico '&&'
	NODE_OR,         // Operador lógico '||'
	NODE_SEQUENCE,   // Secuencia de comandos ';' o newline
	NODE_PIPE,       // Pipe '|'
	NODE_ASSIGNMENT, // Asignación '='
	NODE_COMMAND     // Comando individual
}	t_nodetype;

int	parser(t_mt **input);
int	tokenize(char *str, t_mt **list);

#endif // INPUT_H