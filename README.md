# Compiler
A simple GCC-like compiler able to compile MemeLanguage for virtual stack machine (see in https://github.com/Mihail-Makei/CPU).
# Compilation description
The process of compilation consists of the following stages:
1. Scanning and tokenization. The code is being scanned and divided into tokens - special structures containing the data about the objects - variables, functions, operators, etc.
2. Parsing the tokens. The tokens are being used to build a tree representing the program.
3. Optimization. Some of the operations reprezented in the tree are optimized (i.e. 100 + 100 is turned into 200).
4. Code generation. The tree is turned into the machine code.
# Language description
The structure of the program is the following:
 - Variables declarations. First, the variables are defined as the following:
 ```
 vars: var1, var2;
 ```
 In case there are no variables used in the program, the list of variables should be left empty with semicolon at the end as shown below:
 ```
 vars: ;
 ```
  - Function names declarations. They must be declared the same way as variables.
 ```
 functions: func1, func2;
 ```
 ```
 functions: ;
 ```
  - Main body of the program. The program begins with the key word 'begin' and finishes with the key word 'end'. It may contain the expressions and the calls of the other functions. The expressions must be finished with semicolon.
```
begin
  var1 =: 1;
  call func1
  output var1;
end.
```
 - The function definitions. The functions are defined the same way as the main body beginning with 'func funcname', where funcname is the name of the function. For example:
```
func func1
begin
  ...
end
```
# Variables
 - All the variables in the language are global. 
 - Variables may have any name except for those starting with semicolon, a number or having the same name or prefix as the keywords.
# Functions
 - The same as variables.
