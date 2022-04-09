# Clcl - console calculator for arithmetic expressions

Console calculator writen in ANSI C for arbitrary arithmetic expressions.

Wrote as an exercise to remember the C and for fun.

```bash
$ ./clcl '(1 + 2) ^ 3 + 3 + 10'
60
```

**Features:**
- no dependencies
- handles brackets of different types and operator precedence
- `EN`, `DE`, `RU` and `KZ` languages support

**Build:**
Depends on `gcc` and `gnu make`.

```bash
# Close the repo
$ git clone https://github.com/nikolay-govorov/clcl.git

# Build the app with GCC
$ make build

# Use the clcl!
$ ./clcl '1 + 3'
```

