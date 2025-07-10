#!/bin/bash

run() {
	cc -lreadline -no-pie  ./*.c ./main_pars/main.c ../lexer/*.c ../libft/libft.a ../utils/fprintf/fprintf.a
	input="$1"
	# leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	mv ./a.out ./main_pars
	./main_pars/a.out "$input"
}


run '<< E cat > out > out1'