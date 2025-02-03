#include "../../minishell.h"

// t_garbage	*init_g(void)
// {
// }

void	ft_free(void *ptr)
{
	static int			i = -1;
	static t_garbage	*garbage;

	if (ptr == ((void *) -1))
	{
		i = -1;
		ft_finishbag(garbage);
		garbage = ft_malloc(-1);
		return ;
	}
	if (!ptr)
		return ;
	if (i == -1)
	{
		garbage = ptr;
		i++;
		return ;
	}
	ft_killnode(&garbage, ptr);
}

void	*ft_malloc(long int l)
{
	static t_garbage	*garbage = NULL;
	void				*ptr;

	if (l == -1)
	{
		garbage = NULL;
		return (NULL);
	}
	if (garbage == NULL)
	{
		garbage = malloc(sizeof(t_garbage));
		if (garbage == NULL)
			return (NULL);
		garbage->ptr = NULL;
		garbage->next = NULL;
		ft_free(garbage);
	}
	ptr = malloc(l);
	if (!ptr)
		return (free(garbage), NULL);
	ft_lstbackadd_garbage(ptr, &garbage);
	return (ptr);
}
