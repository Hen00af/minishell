# as beautiful as a shell

this is a project making bash like program in C, but it's minimum.

this include function to deal options

## these builtin command 

```sh
"cd"
    change directry
"pwd"
    now corrent directry
"env"
    put  environment args
"echo" with option "-n"
    put word with next line (or wothout when it's with -n)
"exit"
    exit current process 
"export"
    export args to environment argument 
"unset"
    unset args to environment argument
these syntax with ast(absolute struct tree)
```
## and these syntax.
```sh
"|"
    connect stdout of left command to stdin of right command (pipe)
"<"
    read input from file (input redirection)
">"
    write output to file (overwrite) (output redirection)
">>"
    append output to file (append redirection)
"<<"
    read inline input until delimiter (heredoc)
"()"
    run command(s) in subshell (new process)
"&&"
    execute right command only if left succeeded (logical AND)
"||"
    execute right command only if left failed (logical OR)
"*"
    match multiple filenames (wildcard / glob)
```

## About the Grammar (CFG)

This shell is built around a Context-Free Grammar (CFG),
which defines how commands and operators combine to form valid shell expressions.

You can view the full CFG and visualize how it constructs an AST (Abstract Syntax Tree) here:

#### 📘 Source Code: [github.com/Hen00af/ast_visualizer]

#### 🌐 Live Visualizer:[hen00af.github.io/ast_visualizer]

### Concept

“As beautiful as a shell.”

The project aims to express the structural beauty of shells —
combining recursion, logic, and minimalism into a single, elegant design.

💻 Built With

C (Standard 42 project style)

Manual memory management (no external libs)

Recursive descent parser

AST-based execution logic

## How to Build
git clone https://github.com/Hen00af/minishell.git
cd minishell
make && ./minishell


Then, you can start playing with your own Minishell 🎮
