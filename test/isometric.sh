#! /usr/bin/bash

cc isometric_main.c ../src/draw.c ../src/rotation.c ../src/funcs.c \
    ../src/colors.c ../src/read_file.c \
    -I../inc -I../lib/minilibx-linux -I../lib/libft/inc \
    ../lib/minilibx-linux/libmlx.a ../lib/libft/lib/libft.a \
    -lm -lX11 -lXext -lz \
    -o ../bin/isometric -g