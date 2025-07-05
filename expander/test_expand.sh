#!/bin/bash

run() {
	cc -no-pie ./main_expander/main.c ../lexer/*.c ../parser/*.c ../linearizer/*.c ../linearizer/main_line/*.c ../signal/*.c ../heredoc/*.c ./*.c  ../libft/libft.a ../utils/*.c ../utils/fprintf/fprintf.a -lreadline
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	mv ./a.out ./main_expander
	./main_expander/a.out "$input"
}


run 'echo ls'