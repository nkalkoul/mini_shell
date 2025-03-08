#include "../../minishell.h"

void	set_oldpwd(t_global *global, char *pwd)
{
	t_env	*env;

	env = global->my_env;
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			ft_free(env->value);
			env->value = ft_strdup(pwd);
			return ;
		}
		env = env->next;
	}
}

void	set_pwd(t_global *global)
{
	t_env	*env;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	env = global->my_env;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			ft_free(env->value);
			env->value = ft_strdup(pwd);
			return ;
		}
		env = env->next;
	}	
}

int	ft_cd(t_taken *taken, t_global *global)
{
	t_taken	*current;
	char	*pwd;

	current = taken->next;
	global->status = 0;
	if (current->next)
	{
		ft_printf("Too many arguments\n");
		global->status = 1;
	}
	pwd = getcwd(NULL, 0);
	if (chdir(current->token) == -1)
	{
		ft_printf("%s: Not a directory\n", current->token);
		global->status = 1;
	}
	set_pwd(global);
	set_oldpwd(global, pwd);
	return (global->status);
}
