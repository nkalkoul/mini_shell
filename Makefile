SRCS =	$(addprefix srcs/taken/, ft_initaken.c ft_parse_rd.c ft_taken_to_cmd.c) \
		$(addprefix srcs/, ft_minishell.c) \
		$(addprefix srcs/utils/, ft_free.c ft_is.c ft_lstbackadd.c ft_printlist.c) \
		$(addprefix srcs/env/, ft_init_env.c ft_expandables.c) \
		$(addprefix srcs/builtins/, ft_export.c ft_unset.c ft_echo.c ft_pwd.c ft_cd.c) \
		$(addprefix srcs/garbage/, ft_garbage.c ft_garb_utils.c) \
		$(addprefix srcs/ast/, ft_ast.c tests_utils.c) \
		$(addprefix srcs/exec/, ft_exec.c ft_exec_utils.c ft_exec_is.c)

CC =	cc -g3 #-Wall -Werror -Wextra
DIRLIB = ./libft
LIBFT = $(DIRLIB)/libft.a
NAME =	minishell
OBJS =	$(SRCS:.c=.o)
VMINI = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--trace-children=yes -s --suppressions=minishell.supp \
        --track-fds=yes --quiet

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "minishell done !"

$(LIBFT) :
	@make -sC $(DIRLIB)


%.o : %.c
	@$(CC) -c $< -o $@ 
	@echo "compiling: $<"

clean :
	@make fclean -sC $(DIRLIB)
	@rm -f $(OBJS)
	@echo "refreeeesh baby"

fclean : clean
	@rm -f $(NAME)

re : fclean all

rlleaks: $(NAME)
	$(VMINI) ./minishell

.PHONY: all clean fclean re rlleaks
