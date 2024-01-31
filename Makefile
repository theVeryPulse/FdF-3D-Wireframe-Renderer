NAME := fdf
FILE := main.c \
	colors.c \
	read_file.c
SRC_DIR := src
OBJ_DIR := build
INC_DIR := inc
MLX_INC := lib/minilibx-linux
MLX_STT := lib/minilibx-linux/libmlx.a
FT_INC := lib/libft/inc
FT_STT := lib/libft/lib/libft.a

CFLAGS := -Wall -Wextra -Werror

SRC := $(addprefix $(SRC_DIR)/, $(FILE))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# -O3 highest optimization
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# $(CC) -I /usr/include -I$(MLX_INC) -O3 -c $< -o $@ -I$(INC_DIR)
	$(CC) -I /usr/include -I$(MLX_INC) -I$(FT_INC) -g -c $< -o $@ -I$(INC_DIR)

.SILENT:

all: $(NAME)

$(NAME): msg $(OBJ) $(MLX_STT) $(FT_STT)
	$(CC) $(OBJ) $(MLX_STT) $(FT_STT) -I$(MLX_INC) -I$(FT_INC) -l Xext -l X11 -lm -lz -o $(NAME) -I$(INC_DIR)
	@echo "👏 Complete! 👏"

msg:
	@echo "🚧 Building fdf... 🏗️"

$(FT_STT):
	$(MAKE) -C lib/libft

$(MLX_STT):
	$(MAKE) -C lib/minilibx-linux all

clean:
	rm -f ./$(OBJ_DIR)/*.o

fclean: clean
	rm -f fdf

re: fclean all

.PHONY: all, clean, fclean, re
