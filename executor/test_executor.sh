#!/bin/bash

run() {
	cc 	 -g -O0 -no-pie \
		../expander/*.c \
		../parser/*.c \
		../lexer/*.c \
		../linearizer/*.c \
		./exec_fank.c \
		./exec_util.c \
		../builtin/*.c \
		../utils/fprintf/fprintf.a \
		./exec_test/main.c \
		../signal/*.c \
		../heredoc/*.c \
		../utils/*.c \
		../libft/libft.a \
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
	wait
}

run "$HOME"
