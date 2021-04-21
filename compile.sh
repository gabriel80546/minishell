#!/usr/bin/dash
compile="gcc -I libft libft/*.c main.c -o main"
compile="gcc -g3 -fsanitize=address -I libft libft/*.c main.c -o main"
echo $compile
$compile
