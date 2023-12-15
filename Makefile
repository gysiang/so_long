Name		:= so_long
CC		:= gcc
FLAGS		:= -Wall -Wextra -Werror

SRCS		:= main.c
OBJS		:= $(SRCS:.c=.o)

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
else
	INCLUDES = -I/opt/X11/include -Imlx
endif

MLX_DIR		= ./mlx
MLX_LIB		= $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -LX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -LX11 -framework OPENGL -framework AppKit
endif


all	: $(MLX_LIB) $(NAME)

.c.o:
		$(cc) $(FLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): 	$(OBJS) $(MLX_LIB)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)


