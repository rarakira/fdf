NAME		=	fdf

SRCS		=	main.c					exit_program.c			\
				init_map.c				init_map_utils.c		\
				register_hooks.c		register_hooks_utils.c	\
				t_point_list_fns.c		map_rotation.c			\
				draw_map.c				draw_map_utils.c		\
				draw_and_color.c		draw_line.c				\
				free_memory.c

OBJS		=	$(SRCS:.c=.o)

D_FILES		=	$(SRCS:.c=.d)

INCLUDES	=	-Iincludes -Iminilibx_macos -Ilibft

H_FILES		=	includes/error_messages.h						\
				includes/fdf.h									\
				includes/libft.h								\
				includes/ft_printf.h							\
				minilibx_macos/mlx.h

LIB			=	ft

LIBDIR		=	libft

XLIB		=	mlx

XLIBDIR		=	minilibx_macos

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

XFLAGS		=	-framework OpenGL -framework AppKit

RM			=	rm -f

all : libs $(NAME)

$(NAME) : $(OBJS) $(LIBDIR)/libft.a
		$(CC) $(OBJS) -L$(LIBDIR) -l$(LIB) -L$(XLIBDIR) -l$(XLIB) $(XFLAGS) -o $(NAME)

%.o : %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

norm_full:
		@norminette ./*.c libft/*.c libft/*/*.c\
					includes/error_messages.h\
					includes/ft_printf.h\
					includes/libft.h includes/fdf.h

norm:
		@norminette ./*.c includes/error_messages.h includes/fdf.h

libs:
		@$(MAKE) -C $(LIBDIR)
		@$(MAKE) -C $(XLIBDIR)

clean:
		@$(RM) $(OBJS) $(D_FILES)
		@$(MAKE) clean -C $(LIBDIR)
		@$(MAKE) clean -C $(XLIBDIR)
		@echo "\033[1;38;5;221m*  MLX objects removed\033[0m"
		@echo "\033[1;38;5;221m*  Fdf objects removed\033[0m"

fclean:	clean
		@$(RM) $(NAME)
		@$(MAKE) fclean -C $(LIBDIR)
		@rm -rf *.dSYM 
		@echo "\033[1;38;5;221m*  Fdf program removed\033[0m"

re:		fclean all

.PHONY: all clean fclean re norm norm_full bonus
