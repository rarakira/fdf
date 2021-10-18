NAME		=	fdf

#SRCS		=	testing-lib.c
SRCS		=	testing-map.c
#SRCS		=	testing-drawing.c

OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	-Iincludes

LIB			=	ft

LIBDIR		=	libft

XLIB		=	mlx

XLIBDIR		=	../source/minilibx_macos

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

GFLAGS		=	-g

XFLAGS		=	-framework OpenGL -framework AppKit

RM			=	rm -f

DEBUG		=	debug

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(OBJS) -L$(XLIBDIR) -l$(XLIB) $(XFLAGS) -o $(NAME)

%.o : %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norm:
		@norminette ./*.c includes/*.h

clean:
		@$(RM) $(OBJS)
		#@$(MAKE) clean -C $(LIBDIR)
		@echo "\033[1;38;5;221m*  Fdf objects removed\033[0m"

fclean:	clean
		@$(RM) $(NAME) $(DEBUG)
		#@$(MAKE) fclean -C $(LIBDIR)
		@echo "\033[1;38;5;221m*  Fdf program removed\033[0m"

re:		fclean all

$(DEBUG):
		clang $(CFLAGS) $(GFLAGS) $(INCLUDES) $(SRCS) -L$(LIBDIR) -l$(LIB) -o $(DEBUG)

leaks_valg: $(DEBUG)
		valgrind --leak-check=full ./$(DEBUG) $(ARGS)

.PHONY: all clean fclean re play norm leaks leaks_valg debug bonus
