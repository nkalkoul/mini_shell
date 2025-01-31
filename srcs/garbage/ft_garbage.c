#include "../../minishell.h"

t_garbage	*init_g(void)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (new == NULL)
		return (NULL);
	
}

void	*ft_malloc(size_t l)
{
	static t_garbage	*garbage;
	void				*ptr;

	if (garbage == NULL)
	{
		garbage = malloc(sizeof(t_garbage));
		if (garbage == NULL)
			return (NULL);
		garbage->ptr = NULL;
	}
	ptr = malloc(l);
	if (!ptr)
		return (free(garbage), NULL);
	ft_lstbackadd_garb(ptr, &garbage);

}
