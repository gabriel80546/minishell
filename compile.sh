#!/usr/bin/dash
compile="gcc -Wall -Wextra -I libft libft/*.c main.c -o main"
compile="gcc -Wall -Wextra -g3 -fsanitize=address -I libft libft/*.c main.c -o main"
echo $compile
$compile
