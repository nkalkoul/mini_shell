SRCS =	$(addprefix srcs/taken/, ft_initaken.c ft_parse_rd.c ft_taken_to_cmd.c ft_parse_lst_taken.c) \
		$(addprefix srcs/, ft_minishell.c) \
		$(addprefix srcs/utils/, ft_free.c ft_is.c ft_lstbackadd.c ft_printlist.c) \
		$(addprefix srcs/env/, ft_init_env.c ft_expandables.c ft_expand_utils.c) \
		$(addprefix srcs/builtins/, ft_export.c ft_unset.c ft_echo.c ft_pwd.c ft_cd.c ft_do_bulding.c ft_exit.c ft_print_export.c) \
		$(addprefix srcs/garbage/, ft_garbage.c ft_garb_utils.c ft_garb_locks.c) \
		$(addprefix srcs/ast/, ft_ast.c tests_utils.c) \
		$(addprefix srcs/exec/, ft_exec.c ft_exec_utils.c ft_exec_is.c ft_redir.c ft_env2d.c ft_check_path.c ft_heredoc.c) \
		$(addprefix srcs/signal/, ft_signal.c)

CC =	cc -g3 #-Wall -Werror -Wextra
DIRLIB = ./libft
LIBFT = $(DIRLIB)/libft.a
NAME =	minishell
VMINI = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--trace-children=yes -s --suppressions=minishell.supp \
        --track-fds=yes --quiet

OBJS_DIR = .objets/

SRCS_DIR = srcs/

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DIR_DUP = mkdir -p $(@D)

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "minishell done !"

$(LIBFT) :
	@make -sC $(DIRLIB)


$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(DIR_DUP)
	@$(CC) -c $< -o $@ 
	@echo "compiling: $<"

clean :
	@make fclean -sC $(DIRLIB)
	@rm -rf $(OBJS_DIR)
	@echo "refreeeesh baby"

fclean : clean
	@rm -rf $(NAME)

re : fclean all

rlleaks: $(NAME)
	$(VMINI) ./minishell

.PHONY: all clean fclean re rlleaks
