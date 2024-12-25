SRCS =	$(addprefix srcs/taken/, ft_initaken.c ft_parse_rd.c ft_taken_utils.c) \
		$(addprefix srcs/, ft_minishell.c) \
		$(addprefix srcs/utils/, ft_free.c ft_is.c)

CC =	cc -g3 #-Wall -Werror -Wextra
DIRLIB = ./libft

LIBFT = $(DIRLIB)/libft.a

NAME =	minishell
OBJS =	$(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "done !"

$(LIBFT) :
	@make -sC $(DIRLIB)


%.o : %.c
	@$(CC) -c $< -o $@ 
	#echo "compiling: $<"

clean :
	make fclean -sC $(DIRLIB)
	rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all