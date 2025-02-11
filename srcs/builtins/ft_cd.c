#include "../../minishell.h"

// int		ft_count_path(char	*pwd)
// {
// 	int		i;
// 	int		count;

// 	i = 1;
// 	count = 0;
// 	while (pwd[i] != '/')
// 		i++;
// 	i++;
// 	while (pwd[i] && pwd[i] != '/')
// 	{
// 		i++;
// 		count++;
// 	}
// 	return (count);
// }

// void	ft_path_cd(t_taken *current, t_global *global)
// {
// 	char	*pwd;
// 	char	*path;

// 	pwd = ft_getenv("PWD", global);
// 	if (pwd == NULL)
// 		return (1);
// 	path = ft_malloc(sizeof(char) * (ft_count_path(pwd) + 1));
// 	while ()
// }

int	ft_cd(t_taken *taken)
{
	t_taken	*current;

	current = taken->next;
	if (current->next)
		return (ft_printf("Too many arguments\n"), 1);
	if (chdir(current->token) == -1)
		return (ft_printf("%s: Not a directory\n", current->token), 1);
	return (0);
}
