#!/bin/bash

run() {
cc  -lreadline ../expander/*.c ../parser/*.c ../lexer/*.c ../linerlizer/*.c ./*.c ../builtin/*.c ../utils/*.c ../utils/fprintf/fprintf.a ../libft/libft.a ./exec_test/main.c ../signal/*.c
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	mv ./a.out ./exec_test
	# valgrind 
	./exec_test/a.out "$input"
}


run '$HOME'