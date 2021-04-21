#!/usr/bin/dash
compile="gcc -Wall -Wextra -O3 -g3 -fsanitize=address -I libft libft/*.c main.c -o main"
compile="gcc -Wall -Wextra -O3 -I libft libft/*.c main.c -o main"
echo $compile
$compile
