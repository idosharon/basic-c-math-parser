this is my super simple math parser, it can evaluate really simple math expressions like:


"1+3.3*(2-1)-2/3" -> 3.6333...<br>
"(8*2-2)+(3-12/2)" -> 11.0<br>
etc...

currently the parser is able process expressions with --,++,*,/,+,-,(,) and numbers with . as decimal seperator
feel free to use it, modify it, find bugs, or whatever you want to do with it

#### run
```bash
make
parse "EXPRESSION"
```

#### add command to path
```bash
export PATH="{PARSE_EXEC_FULL_PATH}:$PATH"
```
