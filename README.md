# RPN Graph Plotter

Terminal-based C application for plotting mathematical functions using lexical analysis, the Shunting Yard algorithm, Reverse Polish Notation, stack-based expression evaluation, and ASCII rendering.

The program reads a mathematical expression `f(x)`, parses it into tokens, converts the expression from infix notation to Reverse Polish Notation, evaluates the expression for a range of `x` values, and renders the resulting graph directly in the terminal.

## Features

- parsing mathematical expressions from a string;
- lexical analysis and token validation;
- conversion from infix notation to Reverse Polish Notation;
- expression evaluation using a stack;
- ASCII graph rendering in the terminal;
- validation of incorrect expressions;
- modular C project structure;
- Makefile-based build.

## Supported operations and functions

The current implementation supports:

- addition: `+`;
- subtraction: `-`;
- multiplication: `*`;
- division: `/`;
- exponentiation: `^`;
- brackets: `(` and `)`;
- variable: `x`;
- functions: `sin`, `cos`, `tan`, `sqrt`, `ln`, `exp`, `fabs`.

## Graph format

The graph is rendered on a fixed terminal field:

- width: `80`;
- height: `25`;
- domain: `[0; 4π]`;
- range: `[-1; 1]`;
- graph symbol: `*`;
- empty space symbol: `.`;
- coordinate axes are not displayed.

## Project structure

```text
rpn-graph-plotter/
├── Makefile
└── src/
    ├── graphics.c
    ├── graphics.h
    ├── lexer_and_check.c
    ├── lexer_and_check.h
    ├── rpn.c
    ├── rpn.h
    ├── shunting_yard.c
    ├── shunting_yard.h
    ├── stack.c
    ├── stack.h
    └── token.h
```

## Modules

### Graphics

The `graphics` module is responsible for reading the input expression, calculating function values across the plotting range, and rendering the graph in the terminal.

### Lexer

The `lexer_and_check` module splits the input expression into tokens and validates numbers, operators, brackets, supported functions, and the variable `x`.

### Shunting Yard

The `shunting_yard` module implements Dijkstra's Shunting Yard algorithm to convert an infix mathematical expression into Reverse Polish Notation.

### RPN Evaluator

The `rpn` module evaluates expressions in Reverse Polish Notation using a stack-based approach.

### Stack

The `stack` module implements a dynamic stack structure used during expression conversion and evaluation.

### Token

The `token` module defines token types, supported function identifiers, and the common token structure used across the project.

## Build

```bash
make
```

The executable file is created in the build directory according to the Makefile configuration.

## Run

```bash
./build/graph
```

Then enter a mathematical expression, for example:

```text
sin(cos(2*x))
```

## Example

Input:

```text
sin(cos(2*x))
```

Example output:

```text
................................................................................
................................................................................
.........***.................**..................**.................***.........
........*...................*..*................*..*...................*........
............*...................*..............*...................*............
.......*...................*........................*...................*.......
.............*...................*............*...................*.............
..........................*..........................*..........................
......*..................................................................*......
..............*..................................................*..............
..................................*..........*..................................
.........................*............................*.........................
.....*....................................................................*.....
...............*................................................*...............
...................................*........*...................................
....*...................*..............................*...................*....
................*..............................................*................
....................................*......*....................................
.......................*................................*.......................
...*.............*............................................*.............*...
......................*..............*....*..............*......................
..*...............*...................*..*...................*...............*..
**.................***.................**.................***.................**
................................................................................
................................................................................
```

The exact visual output may differ slightly depending on expression values and rounding.

## Error handling

If the input expression cannot be parsed or evaluated correctly, the program prints:

```text
n/a
```

Invalid cases include:

- unsupported symbols;
- unknown functions;
- incorrect operators;
- unbalanced brackets;
- empty brackets;
- invalid bracket nesting;
- invalid mathematical expressions;
- expressions that cannot be evaluated correctly for plotting.

## Technologies

- C;
- Makefile;
- standard C libraries;
- `math.h`;
- dynamic memory allocation;
- stack data structure;
- lexical analysis;
- Shunting Yard algorithm;
- Reverse Polish Notation;
- ASCII rendering.

## Skills demonstrated

This project demonstrates:

- structured programming in C;
- modular program decomposition;
- working with pointers and dynamic memory;
- implementing a stack data structure;
- parsing mathematical expressions;
- validating user input;
- converting infix expressions to Reverse Polish Notation;
- evaluating expressions through RPN;
- rendering function graphs in a terminal.
