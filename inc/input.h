#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
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
t_mt			*tokenize(char *str);

/* Add a node to the binary tree */
t_mt			*add_node(t_mt *root, t_mt *node);
t_mt			*create_node(char *data);
t_mt			*create_node_with_children(char *value, t_mt *children);

/* Parse a token and add it to the tree */
void			parse_token(char *input, int *i, t_mt **tree);

/* Helpers */

int				is_operator_token(char *token, int *i);
int				has_higher_precedence(char *op1, char *op2);
int				is_whitespace(char c);
int				is_quoted(char c);
int				is_operator(char c);

void			add_token(t_mt **tokens, char *token);
char			*extract_quoted_token(char *str, int *i);
char			*extract_operator_token(char *str, int *i);
char			*extract_word_token(char *str, int *i);

void			process_token(char *input, int *i, t_mt **tree);
void			process_word(char *input, int *i, t_mt **tree);
void			process_operator(char *input, int *i, t_mt **tree);
void			process_parentheses(char *input, int *i, t_mt **tree);

#endif // INPUT_H