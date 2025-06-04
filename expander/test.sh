#!/bin/bash

run_test(){
	prev_status="$1"

    gcc expander.c -o test ../libft/libft.a
    ./test "$prev_status"
    echo "return code: $?"
}

some_command   # ここで何かを実行
run_test "$?"  # その終了コードをCに渡す
