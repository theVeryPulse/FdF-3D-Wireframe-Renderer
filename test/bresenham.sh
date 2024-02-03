#! /usr/bin/bash

mkdir -p ../build

cc bresenham_main.c ../src/draw.c ../src/rotation.c -I../inc \
    -I../lib/minilibx-linux -I../lib/libft/inc ../lib/minilibx-linux/libmlx.a \
    ../lib/libft/lib/libft.a -o ../bin/bresenham -lX11 -lXext -lm -lz -g

../bin/bresenham
