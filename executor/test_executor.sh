#!/bin/bash

run() {
	cc 	-no-pie \
		../expander/*.c \
		../parser/*.c \
		../lexer/*.c \
		../linerlizer/*.c \
		./*.c \
		../builtin/*.c \
		../utils/*.c \
		../utils/fprintf/fprintf.a \
		../libft/libft.a \
		./exec_test/main.c \
		../signal/*.c \
		-lreadline

	if [ $? -ne 0 ]; then
		echo "❌ コンパイルに失敗しました"
		exit 1
	fi

	input="$1"

	mv ./a.out ./exec_test || {
		echo "❌ a.out の移動に失敗しました"
		exit 1
	}

	./exec_test/a.out "$input"
}

run "$HOME"
