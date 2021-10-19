NAME		=	fdf

SRCS		=	main.c									\
				init_map.c			init_map_utils.c	\
				draw_map.c	

OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	-Iincludes

H_FILES		=	includes/error_messages.h				\
				includes/fdf.h							\
				includes/libft.h						\
				includes/ft_printf.h					\
				includes/mlx.h

LIB			=	ft

LIBDIR		=	libft

XLIB		=	mlx

XLIBDIR		=	minilibx_macos

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

GFLAGS		=	-g

XFLAGS		=	-framework OpenGL -framework AppKit

RM			=	rm -f

DEBUG		=	debug

all : libs $(NAME)

$(NAME) : $(OBJS) $(H_FILES)
		$(CC) $(OBJS) -L$(LIBDIR) -l$(LIB) -L$(XLIBDIR) -l$(XLIB) $(XFLAGS) -o $(NAME)

%.o : %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norm:
		@norminette ./*.c libft/*.c libft/*/*.c\
					includes/error_messages.h\
					includes/ft_printf.h\
					includes/libft.h

libs:
		@$(MAKE) -C $(LIBDIR)
		@$(MAKE) -C $(XLIBDIR)

clean:
		@$(RM) $(OBJS)
		@$(MAKE) clean -C $(LIBDIR)
#		@$(MAKE) clean -C $(XLIBDIR)
		@echo "\033[1;38;5;221m*  MLX objects removed\033[0m"
		@echo "\033[1;38;5;221m*  Fdf objects removed\033[0m"

fclean:	clean
		@$(RM) $(NAME) $(DEBUG)
		@$(MAKE) fclean -C $(LIBDIR)
		@rm -rf *.dSYM 
		@echo "\033[1;38;5;221m*  Fdf program removed\033[0m"

re:		fclean all

$(DEBUG):
		clang $(CFLAGS) $(GFLAGS) $(INCLUDES) $(SRCS) -L$(LIBDIR) -l$(LIB) -o $(DEBUG)

leaks_valg: $(DEBUG)
		valgrind --leak-check=full ./$(DEBUG) $(ARGS)

.PHONY: all clean fclean re play norm leaks leaks_valg debug bonus
