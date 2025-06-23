#!/bin/bash

run() {
	cc -lreadline  ../lexer/*.c ../parser/*.c ../linerlizer/*.c ./*.c  ../libft/libft.a ../utils/init_env.c
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	./a.out "$input"
}


run '$HOME'