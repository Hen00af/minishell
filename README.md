# as beautiful as a shell

this is a project making bash like program in C, but it's minimum.

this include function to deal options

these builtin command 

```
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
and these syntax.
```
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

for making this, I made "Context-free Grammar"(CFG)
about it
[CFG] https://github.com/Hen00af/docs/CFG/
