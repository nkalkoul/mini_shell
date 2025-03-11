#include "../../minishell.h"

char	**ft_addtab(char **tab, char *red)
{
	char	**new;
	int		i;

	i = 0;
	if (!tab)
	{
		tab = ft_malloc(sizeof(char *) * 1);
		tab[0] = 0;
	}
	new = ft_malloc(sizeof(char *) * (ft_countdouble(tab) + 2));
	if (!new)
		return (NULL);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = ft_strdup(red);
	new[++i] = 0;
	return (new);
}

char	**ft_newread(t_files *files)
{
	char	**redir;
	char	*red;
	int		i;

	i = 0;
	redir = NULL;
	while (1)
	{
		red = readline("heredoc> ");
		if (red == NULL)
			return (NULL);
		if (ft_strcmp(files->path, red) == 0)
			break ;
		redir = ft_addtab(redir, red);
		if (redir == NULL)
			return (NULL);
	}
	return (redir);
}
