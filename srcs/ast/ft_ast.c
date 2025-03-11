#include "../../minishell.h"

void	print_AST_test(t_cmd *command);

t_cmd	*ast_recursive(t_cmd *left, t_cmd *top, int weight);

t_cmd	*ft_ast(t_cmd *first)
{
	t_cmd	*tmp;

	tmp = ast_recursive(first, first->next, 0);
	return (tmp);
}

t_cmd	*next_cmd_ast(t_cmd *first, int poids_de_lenvoyeur)
{
	t_cmd	*tmp;

	tmp = ast_recursive(first, first->next, poids_de_lenvoyeur);
	return (tmp);
}

int	operateur_into_poid(t_cmd *top)
{
	if (top == NULL)
		return (0);
	if (top->type == OR || top->type == AND)
		return (1);
	else if (top->type == PIPE)
		return (2);
	return (0);
}

t_cmd	*last_used_cmd(t_cmd *ast_top)
{
	while (ast_top->right)
		ast_top = ast_top->right;
	return (ast_top);
}

t_cmd	*ast_recursive(t_cmd *left, t_cmd *top, int weight)
{
	t_cmd	*next_cmd;

	if (top == NULL || operateur_into_poid(top) <= weight)
		return (left);
	top->left = left;
	left->top = top;
	top->right = next_cmd_ast(top->next, operateur_into_poid(top));
	next_cmd = last_used_cmd(top->right);
	top->right->top = top;
	return (ast_recursive(top, next_cmd->next, weight));
}
