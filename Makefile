NAME := fdf
CC := gcc
TRANSFORMATION_MATRIX_DIR := transformation_matrix
TRANSFORMATION_MATRIX_FILES := \
	isometric4x4.c \
	rotation.h \
	rotation4x4_for_key.c \
	scale4x4_for_key.c \
	transformation_matrix.h \
	translation4x4_for_key.c \
	x_rotation4x4.c \
	y_rotation4x4.c \
	z_rotation4x4.c
TRANSFORMATION_MATRIX_FILES := $(addprefix $(TRANSFORMATION_MATRIX_DIR)/, $(TRANSFORMATION_MATRIX_FILES))


BRESENHAM_DIR := bresenham
BRESENHAM_FILES := \
	bresenham_draw_colored_line.c \
	bresenham_draw_colored_pixels.c \
	bresenham_normalize_coords.c
BRESENHAM_FILES := $(addprefix $(BRESENHAM_DIR)/, $(BRESENHAM_FILES))


MAP_DIR := map
MAP_FILES := \
	map_build.c \
	map_check.c \
	map_parse_data.c \
	map_populate_vertexes.c
MAP_FILES := $(addprefix $(MAP_DIR)/, $(MAP_FILES))


HEX_ATOI_DIR := hex_atoi
HEX_ATOI_FILES := \
	hex_atoi.c
HEX_ATOI_FILES := $(addprefix $(HEX_ATOI_DIR)/, $(HEX_ATOI_FILES))


COORD_CONVERSION_DIR := coord_conversion
COORD_CONVERSION_FILES := \
	raster_coord.c \
	screen_coord_caval.c \
	screen_coord_ortho.c
COORD_CONVERSION_FILES := $(addprefix $(COORD_CONVERSION_DIR)/, $(COORD_CONVERSION_FILES))


EVENTS_HANDLERS_DIR := event_handlers
EVENTS_HANDLERS_FILES := \
	destroy_exit.c \
	handle_key_cavalier.c \
	handle_key_isometric.c \
	mouse_motion.c \
	moust_button.c \
	transform.c
EVENTS_HANDLERS_FILES := $(addprefix $(EVENTS_HANDLERS_DIR)/, $(EVENTS_HANDLERS_FILES))


COMMON_FILES := \
	argb.c \
	image.c \
	key_hooks.c \
	matrix.c \
	read_file.c \
	render.c \
	transform.c \
	$(TRANSFORMATION_MATRIX_FILES) \
	$(BRESENHAM_FILES) \
	$(MAP_FILES) \
	$(COORD_CONVERSION_FILES) \
	$(HEX_ATOI_FILES) \
	$(EVENTS_HANDLERS_FILES)

SRC_DIR := src
OBJ_DIR := build


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
	mkdir -p $(@D)
	$(CC) -I /usr/include -I$(MLX_INC) -I$(FT_INC) -O3 -c $< -o $@

# .SILENT:

all: $(NAME)

$(NAME): $(OBJ) $(MLX_STT) $(FT_STT)
	@rm -f bonus
	$(CC) $(OBJ) $(MLX_STT) $(FT_STT) -I$(MLX_INC) -I$(FT_INC) -l Xext -l X11 -lm -lz -o $@
	@echo "👏 Complete! 👏"

bonus: $(OBJ_BONUS) $(MLX_STT) $(FT_STT)
	touch bonus
	$(CC) $(OBJ_BONUS) $(MLX_STT) $(FT_STT) -I$(MLX_INC) -I$(FT_INC) -l Xext -l X11 -lm -lz -o $(NAME)
	@echo "👏 Complete! 👏"

$(FT_STT):
	$(MAKE) -C lib/libft

$(MLX_STT):
	$(MAKE) -C lib/minilibx-linux all

clean:
	rm -rf ./$(OBJ_DIR)
	$(MAKE) -C lib/libft clean
	$(MAKE) -C lib/minilibx-linux clean


fclean: clean
	rm -f bonus
	rm -f fdf
	rm -f lib/libft/lib/libft.a
	rm -f lib/libft/lib/*.a

re: fclean all

.PHONY: all, clean, fclean, re





















