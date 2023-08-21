# Notes

## What does A-- supports until now?

### Keywords
* **`log`** - like `print()`
    * **Tip**: If you put a `-` after the `log` string, it will have no new line
    * **Tip**: If you put a `~` in the `log` string, it adds a new line
* **`input`** - but cannot *use*/*store* that input
* **`var`** - declares vars: `var var_name: type = value;`
* **`getvar`** - gets a variable based on its **M-Address**
* **`getvars`** - ***DEV TOOL*** gets all the vars with their properties

## Commands to run
* **`gcc runner.cpp -lstdc++ -o amm_compiler`**
* **`./amm_compiler program.amm`**