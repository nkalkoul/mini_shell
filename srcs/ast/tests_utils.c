// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tests_utils.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/10 05:33:34 by ibaby             #+#    #+#             */
// /*   Updated: 2025/03/11 11:31:33 by modavid          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../minishell.h"

// char		*type_to_str(int type);
// void		print_command(t_cmd *command);
// char		*operator_type_to_str(int type);
// void		printTree(t_cmd *command, int depth, int isRight, int *branch);

// void	print_AST_test(t_cmd *command)
// {
// 	int array[1024] = {0};

// 	printTree(command, 0, 0, array);
// }

// void print_command(t_cmd *command)
// {
// 	int 	i;

// 	i = -1;
//     if (command->type == 0)
//     {
// 		printf("%s", command->arg_cmd[++i]);
// 		while (command->arg_cmd && command->arg_cmd[++i] != NULL)
// 		{
// 			printf("  (\"%s\")", command->arg_cmd[i]);
// 		}
// 	}
// 	else
// 		printf ("%s", operator_type_to_str(command->type));
// }

// void printTree(t_cmd *command, int depth, int isRight, int *branch) {
//     if (depth > 0) {
//         for (int i = 0; i < depth - 1; i++) {
//             if (branch[i]) printf("│   ");
//             else printf("    ");
//         }
//         printf("%s", isRight ? "└──" : "├──");
//     }

//     if (command == NULL) {
//         printf("NULL\n");
//         return;
//     }

//     print_command(command);
//     printf("\n");

//     if (command->left != NULL || command->right != NULL) {
//         branch[depth] = (command->right != NULL);
//         printTree(command->left, depth + 1, command->right == NULL, branch);
//         printTree(command->right, depth + 1, 1, branch);
//     }
// }

// char *operator_type_to_str(int type)
// {
// 	if (type == AND)
// 		return (ft_strdup("AND"));
// 	if (type == OR)
// 		return (ft_strdup("OR"));
// 	if (type == PIPE)
// 		return (ft_strdup("PIPE"));
// 	return (NULL);
// }

// char *type_to_str(int type)
// {
// 	if (type == 0)
// 		return (ft_strdup("CMD"));
// 	if (type == PIPE || type == OR || type == AND)
// 		return (ft_strdup("OPERATOR"));
// 	return (NULL);
// }
