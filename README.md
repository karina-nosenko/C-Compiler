# Compiler from "Another Language" to C

## Prerequisites
The next tools should be installed to successfully compile this project
* bison
* flex
* make

## Usage
1) Edit the <b>input.txt</b> file with a syntax of "Another Language" or leave the default example<br>
2) <b>Compile:</b> make<br>
4) Note the <b>output.c</b> file was created. It contains a c code compiled from the "Another Language"<br>
3) <b>Run:</b> .\program.exe

## "Another Language" syntax
```
begin
    int i, fAvg;
    arr fib;
    fib:(0) = 0;
    fib:(1) = 1;
    i=2;
    print 0, 0;
    print 1, 1;

    while (i<16) do
        begin
            fib:(i) = fib:(i - 2) + fib:(i - 1);
            print i, fib:(i);
            i=i+1;
        end

    print fib@[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1];
    fAvg = (fib@[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) /16;
    print fAvg;
end
```

### Builtin Data types:
<b>int</b> Same definition as int in C/C++<br>
<b>arr</b> Array of zero or more int’s. The size of the arr is dynamic and increases as needed.<br>

### Constants/Literals:
<b>int</b> -- as for int in C Example: 4, 1055, -23, 0<br>
<b>arr</b> -- [int1, int2, …, intn] Example: [1, 2, 3], [-5, 0, 4, -1], [2], []<br>

### Variable definition:
<b>int i;</b> -- An int variable (just like in C/C++)<br>
<b>arr a;</b> -- An arr variable (initially it is an empty array, having 0 elements)<br>

### Variable Naming:
A variable name must begin with a letter or ‘_’ optionally followed by alphanumeric (letters
or digits), up to 32 characters.

### Operators (in decreasing precedence order):
<b>(…)</b> - Parenthesis (as in C)<br>
<b>@</b> - Dot-product<br>
<b>+  -  *  /</b>  - Function/Associativity/Precedence as in C<br>
<b>:</b> - Indexing<br>
<b>=</b> - Assignment (as in C)<br>

### Expressions
<img width="431" alt="image" src="https://user-images.githubusercontent.com/77194094/180665671-8e356a05-e2c4-4d3f-b61b-3557ca66897b.png">

