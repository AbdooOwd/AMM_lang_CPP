# A-- Programming Language Documentation

## Introduction
A-- is a simple programming language made for fun. It features simple stuff.
The only original thing in this language is the [**M-Address**]()

## Table of Contents
- [Keywords](#keywords)
- [Data Types](#data-types)
- [Functions](#functions)
- [Math Operations](#math-operations)
- [Variables](#variables)
- [Input and Output](#input-and-output)
- [Comments](#comments)
- [M-Addresses](#m-address)
- [Examples](#examples)
- [Getting Started](#getting-started)

## Keywords
The following keywords are available in A--:
- `whatif`: ***WIP***
- `orelse`: ***WIP***
- `endif`: ***WIP***
- `log`: Prints to the console (see [log](#log))
- `input`: Lets the user enter input (see [input](#input))
- `var`: Used to declare variables (see [variables](#variables))
- `math`: Lets the program execute simple math (see [math](#math-operations))

## Data Types
A-- supports the following data types:
- `int`
- `float`
- `str`
- `bool`
- `array`

## Math Operations
The `math` keyword allows you to perform basic math operations. You can use the following math operators:
- `+`: Addition
- `-`: Subtraction
- `*`: Multiplication
- `/`: Division

## Variables
Variables in A-- can be declared using the `var` keyword. Example:
```A--
var myVariable: int = 42;
```

## Input and Output
### `log`
You can use the log keyword to print output to the console. Example:

```A
log "Hello, world!";
```

### `input`
The input keyword allows you to take user input. Example:
```A
input;
```


## Comments
Comments in A-- are denoted by the # symbol. Example:

```A
# This is a comment
```

## M-Addresses
An **M-Address** is the number used to get a variable in A-- (see [variables](#variables))
Example:
```A
var name: str = "AbdooOwd";
getvar 0;
```
Because I am too lazy to make the interpreter get the variable
by using its name, it uses its 'M-Address'. And we see that we 
use `getvar` to get the variable's value using its **M-Address**.

## Examples
Here are some examples of A-- code snippets:

### Example 1: Basic Output
```A
log "Hello, world!";
```

### Example 2: Variable Declaration
```A
var x: int = 5;
var message: str = "Hello";
```

### Example 3: Math Operation
```A
math . 5 + 3;
```


# Getting Started
To get started with A--, follow these steps:

* Install the compiler
* Write your A-- code in a .amm file
* Compile and run your code

For more details and examples, refer to the official documentation.

You can save this content as a `.md` file and edit it further to suit your needs. If you have any more questions or need assistance, feel free to ask!


