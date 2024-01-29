NAME := fdf
FILE := main.c \
	colors.c
SRC_DIR := src
OBJ_DIR := build
INC_DIR := inc
MLX_INC := lib/minilibx-linux
MLX_STT := lib/minilibx-linux/libmlx.a

CFLAGS := -Wall -Wextra -Werror

SRC := $(addprefix $(SRC_DIR)/, $(FILE))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# -O3 highest optimization
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# $(CC) -I /usr/include -I$(MLX_INC) -O3 -c $< -o $@ -I$(INC_DIR)
	$(CC) -I /usr/include -I$(MLX_INC) -g -c $< -o $@ -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ) $(MLX_STT)
	$(CC) $(OBJ) $(MLX_STT) -I$(MLX_INC) -l Xext -l X11 -lm -lz -o $(NAME) -I$(INC_DIR)

$(MLX_STT):
	$(MAKE) -C lib/minilibx-linux all

clean:
	rm -f ./$(OBJ_DIR)/*.o

fclean: clean
	rm -f fdf

re: fclean all

.PHONY: all, clean, fclean, re
