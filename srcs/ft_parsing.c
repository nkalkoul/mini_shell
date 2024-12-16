#include "../minishell.h"

void    ft_parse_rd(char *rd)
{
    char    *cmd;
    int        i;

    i = 0;
    while (rd[i] == ' ' || rd[i] == '\t' || rd[i] == '\v')
        i++;
    while (rd[i] != '\0')
    {
        while ((rd[i] >= 'a' && rd[i] <= 'z') || (rd[i] >= 'A' && rd[i] <= 'Z')
            || rd[i] == 44 || rd[i] <= 34)
        {
            cmd[i] = rd[i];
            i++;
        }
        if (!cmd || access(cmd, X_OK) == 0)
            return ;
        
    }
}
