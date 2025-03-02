#include "../../minishell.h"

int	ft_count_node_env(t_global *global)
{
	t_env	*env;
	int		i;

	env = global->my_env;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i + 1);
}

char	**ft_put_env2d(t_global *global)
{
	t_env	*env;
	char	**tab;
	int		i;

	env = global->my_env;
	i = 0;
	tab = malloc(sizeof(char *) * ft_count_node_env(global));
	if (!tab)
		return (NULL);		// free
	while (env)
	{
		tab[i] = ft_strdup("");
		tab[i] = ft_re_strjoin(tab[i], env->key);
		tab[i] = ft_re_strjoin(tab[i], "=");
		tab[i] = ft_re_strjoin(tab[i], env->value);
		if (!tab[i])
			return (ft_free2d(tab), NULL);		// free
		env = env->next;
		i++;
	}
	tab[i] == NULL;
	return (tab);
}

void	ft_open_redirGG(t_files *files)
{
	int	
}

void	ft_open_redirG(t_files *files)
{
	int	fd;

	fd = open(files->path, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror(files->path);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_open_redirDD(t_files *files)
{
	int	fd;

	fd = open(files->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(files->path);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_open_redirD(t_files *files)
{
	int	fd;

	fd = open(files->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(files->path);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_open_files(t_cmd *cmd)
{
	t_files *files;

	files = cmd->files;
	while (files)
	{
		if (files->type == REDIRD)
			ft_open_redirD(files);
		else if (files->type == REDIRDD)
			ft_open_redirDD(files);
		else if (files->type == REDIRG)
			ft_open_redirG(files);
		else if (files->type == REDIRGG)
			ft_open_redirGG(files);
		files = files->next;
	}
}

char	*ft_split_value(char *cmd, char *value)
{
	char	**tab;
	int		i;

	tab = ft_split(value, ':');
	if (!tab)
		return (NULL);			// free
	i = -1;
	while (tab[++i])
	{
		tab[i] == ft_re_strjoin(tab[i], "/");
		tab[i] == ft_re_strjoin(tab[i], cmd);
		if (access(tab[i], X_OK) == 0)
			break ;
	}
	if (tab[i] == NULL)
		return (ft_free2d(tab), NULL);		// free
	return (ft_free2d(tab), ft_strdup(tab[i]));		// free
}

char	*ft_pathfinder(t_cmd *cmd, t_global *global)
{
	t_env	*env;

	env = global->my_env;
	if (!env)
		return (NULL);		// free
	if (!cmd->arg_cmd)
		exit(1);			// free
	if (access(cmd->arg_cmd[0], X_OK) == 0)
		return (ft_strdup(cmd->arg_cmd[0]));
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
			break ;
		env = env->next;
		if (!env)
			return (NULL);		// free
	}
	return (ft_split_value(cmd->arg_cmd[0], env->value));
}

void	ft_exec(t_cmd *cmd, t_global *global)
{
	char	*path;
	char	**env;

	// etape 1 ouvrir les fichier 
	ft_open_files(cmd);
	// etape 2 verifier les chemin
	path = ft_pathfinder(cmd, global);
	if (!path)
		return (perror(cmd->arg_cmd[0]), exit(127));		// free
	// etape 3 execve
	env = ft_put_env2d(global);
	if (!env)
		return (ft_putendl_fd("Error env", 2), exit(127));	// free
	if (execve(path, cmd->arg_cmd, env) == -1)
	{
		perror(cmd->arg_cmd[0]);
		ft_free2d(env);
		ft_free2d(cmd->arg_cmd);
		free(path);
		//	free
		exit(1);
	}
}

void	ft_one_command(t_cmd *cmd, t_global *global, t_taken *taken)
{
	pid_t	pid;
	int		status;

	if (ft_isbulding(cmd->arg_cmd) == true)
	{
		//do bulding
	}
	else
	{
		pid = ft_fork();
		if (pid == 0)
		{
			ft_exec(cmd, global);
		}
		waitpid(pid, &status, 0);
	}
}

void	ft_explore_ast(t_cmd *node, t_global *global, t_taken *taken)
{
	if (node->type == AND)
		ft_isand(node, global, taken);
	else if (node->type == OR)
		ft_isor(node, global, taken);
	else if (node->type == PIPE)
		ft_ispipe(node, global, taken);
	else if (node->type == WORD)
		ft_isword(node, global, taken);
}

void	ft_execution(t_cmd *cmd, t_global *global, t_taken *taken)
{
	cmd = ft_ast(cmd);
	if (cmd->type == WORD)
	{
		ft_one_command(cmd, global, taken);
	}
	else
		ft_explore_ast(cmd, global, taken);
}

// void	ft_exec_command(t_cmd *command, t_global *emv)
// {
// 	ft_pathfinder();

// }

