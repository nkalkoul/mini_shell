SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_memset.c ft_strlen.c ft_strlcpy.c ft_strncmp.c \
		ft_memmove.c ft_memcpy.c ft_strlcat.c ft_bzero.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c \
		ft_strdup.c ft_substr.c ft_strtrim.c ft_atoi.c \
		ft_strjoin.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c \
		get_next_line_utils.c ft_free_double.c ft_printf.c \
		ft_put.c ft_puthexa.c ft_strcmp.c

FBONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c
CC =	gcc -Wall -Werror -Wextra -g
#CFLAGS =	-Wall -Werror -Wextra
NAME =	libft.a
OBJS =	$(SRCS:.c=.o)
OBJBONUS = $(FBONUS:.c=.o)

all : $(NAME) #EXEC

$(NAME): $(OBJS)
	@ar -rsc $(NAME) $(OBJS)

#EXEC : main.c
#	$(CC) main.c $(NAME)

%.o : %.c
	@$(CC) -c $(SRCS) $(FBONUS)
	@echo "compiling the libft"

bonus : $(OBJBONUS)
	@ar -rsc $(NAME) $(OBJBONUS)

clean :
	@rm -f $(OBJS) $(OBJBONUS)
	@echo "cleaning the libft"
fclean : clean
	@rm -f $(NAME)

re : fclean all