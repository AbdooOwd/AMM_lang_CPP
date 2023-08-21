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
- [M-Addresses](#m-addresses)
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
- `getvar`: Retrieves the value of a variable using its M-Address (see [getvar](#getvar))
- `getvars`: Displays the values of all variables (see [getvars](#getvars))

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

### `getvar`
The `getvar` keyword allows you to retrieve the value of a variable using its M-Address. Example:

```
var name: str = "AbdooOwd";
getvar 0;
```
### `getvars`
The `getvars` keyword displays the values of all variables. Example:

```
getvars;
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

```
# This is a comment
```
## M-Addresses
An M-Address is the number used to get a variable in A-- (see variables)
Example:

```
var name: str = "AbdooOwd";
getvar 0;
```

Because I am too lazy to make the interpreter get the variable
by using its name, it uses its 'M-Address'. And we see that we
use getvar to get the variable's value using its M-Address.

## Examples
Here are some examples of A-- code snippets:

### Example 1: Basic Output
```
log "Hello, world!";
```

### Example 2: Variable Declaration

```
var x: int = 5;
var message: str = "Hello";
```

### Example 3: Math Operation

```
math _ 5 + 3;
```

### Example 4: Retrieving Variable Value

```
var name: str = "AbdooOwd";
getvar 0;
```

### Example 5: Displaying All Variables

```
getvars;
```
## Getting Started
To get started with A--, follow these steps:

Install the compiler
Write your A-- code in a .amm file
Compile and run your code
For more details and examples, refer to the official documentation.