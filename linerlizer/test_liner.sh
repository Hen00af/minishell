#!/bin/bash

run() {
	cc ../lexer/*.c ../parser/*.c ./*.c  ../libft/libft.a  ./main_line/main.c ../utils/fprintf/fprintf.a
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	mv ./a.out ./main_line
	./main_line/a.out "$input"
}


run 'ls | ls | ls || ls || ls'