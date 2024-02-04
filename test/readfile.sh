#! /usr/bin/bash

cc readfile_main.c ../src/read_file.c \
    -I../inc -I../lib/minilibx-linux -I../lib/libft/inc \
    ../lib/minilibx-linux/libmlx.a ../lib/libft/lib/libft.a \
    -o ../bin/readfile -lX11 -lXext -lm -lz -g