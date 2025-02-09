#include "../../minishell.h"

int	ft_pwd(t_global *global)
{
	char	*pwd;

	pwd = ft_getenv("PWD", global);
	if (pwd == NULL)
		return (1);
	ft_printf("%s\n", pwd);
	return (0);
}
