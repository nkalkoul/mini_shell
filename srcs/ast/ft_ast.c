#include "../../minishell.h"

void	print_AST_test(t_cmd *command);

t_cmd	*ast_recursive(t_cmd *left, t_cmd *top);

t_cmd	*ft_ast(t_cmd *first)
{
	t_cmd	*tmp;

// ft_printcmd
	tmp = ast_recursive(first, first->next);
	print_AST_test(tmp);
	return (tmp);
}

t_cmd	*ast_recursive(t_cmd *left, t_cmd *top) {

	t_cmd	*right;

	if (top == NULL)
		return (left);
	top->left = left;
	left->top = top;

	right = top->next;

	top->right = right;
	right->top = top;

	return (ast_recursive(top, right->next));
}

//			  |
//		    /  \
//		  |	   cat
//		/   \
//	  ls	cat


// ls | cat | cat
