# What is CFG (Context-Free Grammar)

A **CFG (Context-Free Grammar)** defines the syntax rules of a language —  
it describes *how commands can be combined* to form valid structures.

In this minishell, CFG is essential to build the **AST (Abstract Syntax Tree)**,  
which represents the logical structure of a command line.

---

### 🧠 Why it's important

- CFG defines the **hierarchy and relationships** between operators (`|`, `&&`, `<`, `()`, etc.)  
- It allows the shell to **parse** commands recursively and accurately.  
- Once parsed, the shell can **execute** them in the correct order according to the AST.

---

### 📜 CFG for this minishell

```sh
S           → AND_OR

AND_OR      → PIPELINE AND_OR_TAIL

AND_OR_TAIL → '&&' PIPELINE AND_OR_TAIL
            | '||' PIPELINE AND_OR_TAIL
            | ε

PIPELINE    → COMMAND_OR_SUBSHELL PIPELINE_TAIL

PIPELINE_TAIL → '|' COMMAND_OR_SUBSHELL PIPELINE_TAIL
              | ε

COMMAND_OR_SUBSHELL → COMMAND
                    | SUBSHELL

COMMAND     → SIMPLE REDIR_LIST
            | SIMPLE
            | REDIR_LIST

REDIR_LIST  → REDIR REDIR_LIST
            | ε

REDIR       → '<' WORD
            | '>' WORD
            | '>>' WORD
            | '<<' WORD

SIMPLE      → WORD WORD*

SUBSHELL    → '(' AND_OR ')'
