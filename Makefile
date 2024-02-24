NAME := fdf
COMMON_FILES := \
	argb.c \
	bresenham.c \
	bresenham_utils.c \
	coord_conversion.c \
	events.c \
	funcs.c \
	gradient.c \
	helpers.c \
	image.c \
	map.c \
	map_utils.c \
	matrix.c \
	read_file.c \
	render.c \
	rotation.c \
	transform.c \
	transform_cavalier.c \
	transform_isometric.c \
	transform_utils.c
SRC_DIR := src
OBJ_DIR := build
INC_DIR := inc

FILES := main_isometric.c $(COMMON_FILES)
SRC := $(addprefix $(SRC_DIR)/, $(FILES))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

FILES_BONUS := main_cavalier.c $(COMMON_FILES)
SRC_BONUS := $(addprefix $(SRC_DIR)/, $(FILES_BONUS))
OBJ_BONUS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_BONUS))

MLX_INC := lib/minilibx-linux
MLX_STT := lib/minilibx-linux/libmlx.a
FT_INC := lib/libft/inc
FT_STT := lib/libft/lib/libft.a

CFLAGS := -Wall -Wextra -Werror


# -O3 highest optimization
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -I /usr/include -I$(MLX_INC) -I$(FT_INC) -O3 -c $< -o $@ -I$(INC_DIR)

# .SILENT:

all: $(NAME)

$(NAME): $(OBJ) $(MLX_STT) $(FT_STT)
	@rm -f bonus
	$(CC) $(OBJ) $(MLX_STT) $(FT_STT) -I$(MLX_INC) -I$(FT_INC) -l Xext -l X11 -lm -lz -o $@ -I$(INC_DIR)
	@echo "👏 Complete! 👏"

bonus: $(OBJ_BONUS) $(MLX_STT) $(FT_STT)
	touch bonus
	$(CC) $(OBJ_BONUS) $(MLX_STT) $(FT_STT) -I$(MLX_INC) -I$(FT_INC) -l Xext -l X11 -lm -lz -o $(NAME) -I$(INC_DIR)
	@echo "👏 Complete! 👏"

$(FT_STT):
	$(MAKE) -C lib/libft

$(MLX_STT):
	$(MAKE) -C lib/minilibx-linux all

clean:
	rm -f ./$(OBJ_DIR)/*.o

fclean: clean
	rm -f bonus
	rm -f fdf

re: fclean all

.PHONY: all, clean, fclean, re
