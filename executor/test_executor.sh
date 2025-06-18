#!/bin/bash

run() {
cc  ../parser/*.c ../lexer/*.c ../linerlizer/*.c ./*.c ../builtin/*.c ../utils/*.c ../libft/libft.a 
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	./a.out "$input"
}


run '$HOME'