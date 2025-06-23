#!/bin/bash

run() {
	 cc -lreadline  signal.c ../libft/libft.a
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	mv ./a.out ./main_signal
	./main_signal/a.out "$input"
}


run 'ls | ls || pwd'