#! /usr/bin/bash

mkdir -p ../build

cc fdf_main.c ../src/draw.c ../src/rotation.c ../src/colors.c ../src/funcs.c \
    ../src/read_file.c ../src/transform.c \
    -I../inc -I../lib/minilibx-linux -I../lib/libft/inc \
    ../lib/minilibx-linux/libmlx.a ../lib/libft/lib/libft.a \
    -lX11 -lXext -lm -lz \
    -o ../bin/fdf \
    -O3

# ../bin/fdf fdf.fdf
