# Ideas

## Variable order / Variable memory address
Why not use numbers to call variables? Like memory addresses?
For example:
```
var username: str = "Abdoo";
var other_username: str = "Amine";
getvar 0;
```
Knowing that the `username` variable have been declared first so it is **0**. So its position in 
the *memory* *(btw, not real memory)* 
so to get `username` we get the variable 0.
I got this idea because it is **WAY WAY easier** to code the "get variable" logic this way.

I could call it: The **M-Address** *(not for "Memory-Address")*