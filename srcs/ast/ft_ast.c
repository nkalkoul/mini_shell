#include "../../minishell.h"

void	print_AST_test(t_cmd *command);

t_cmd	*ast_recursive(t_cmd *left, t_cmd *top);

t_cmd	*ft_ast(t_cmd *first)
{
	t_cmd	*tmp;

	tmp = ast_recursive(first, first->next);
	print_AST_test(tmp);
	return (tmp);
}

t_cmd	*first_pyramide(t_cmd *left, t_cmd *top)
{
	t_cmd	*right;

	top->left = left;
	left->top = top;
	right = top->next;
	top->right = right;
	right->top = top;
	return (ast_recursive(top, right->next));
}

t_cmd	*ast_recursive(t_cmd *left, t_cmd *top) {

	t_cmd	*right;

	if (top == NULL)
		return (left);
	if (top->type == PIPE)
	{
		left->right = top;
		top->top = left;
		top->left = left->next;
		left->next->top = top;
		if (top->next->next && top->next->next->type == PIPE)
		{
			top->right = top->next->next;
			top->next->next->top = top;
			return (ast_recursive(top, top->next->next));
		}
		else
		{
			top->right = top->next;
			top->next->top = top;
			return (ast_recursive(left, top->next->next));
		}
	}
	else
	{
		top->left = left;
		left->top = top;
		right = top->next;
		top->right = right;
		right->top = top;
		return (ast_recursive(top, right->next));
	}
}

//			  |
//		    /  \
//		  |	   cat
//		/   \
//	  ls	cat


// ls || cat | cat | ws && ls

// t_cmd	*ast_recursive(t_cmd *left, t_cmd *top) {

// 	t_cmd	*right;

// 	if (top == NULL)
// 		return (left);
// 	if (top->type)
// 	{	




// 		return (ast_recursive(rjhr, euge));
// 	}
// 	top->left = left;
// 	left->top = top;
// 	right = top->next;

// 	top->right = right;
// 	right->top = top;

// 	return (ast_recursive(top, right->next));
// }
