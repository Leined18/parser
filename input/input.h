#ifndef INPUT_H
# define INPUT_H

# include "mt.h"

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
}				t_nodetype;

t_hash_table	*parser(char *input);
void			parse_token(char *str, int *i, t_mt **tokens);
t_mt			*tokenize(char *str);

#endif // INPUT_H