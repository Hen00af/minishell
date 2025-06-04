#!/bin/bash
assert() {
	input="$1"
	leak_check=(valgrind -q --leak-check=full)
	#if you want to check leaking, add this command "${leak_check[0]}" to head of ↓
	./a.out "$input"
}

assert "(ls || pwd) && (cat && cat) | ls > out | cat $HOME"

# assert "ls && (ls | cat)"
# echo ---------------
# assert "(ls && ls) |cat "
