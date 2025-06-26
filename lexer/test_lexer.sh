#!/bin/bash

run() {
	cc -lreadline -no-pie ./*.c ../libft/libft.a ./main_lex/main.c ../utils/fprintf/fprintf.a
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	mv ./a.out ./main_lex
	./main_lex/a.out "$input"
}


run 'echo nando'