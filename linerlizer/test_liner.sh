#!/bin/bash

run() {
	cc ../lexer/*.c ../parser/*.c ./*.c  ../libft/libft.a 
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	./a.out "$input"
}


run "ls | ls  | ls && ls  || ls | *.c"