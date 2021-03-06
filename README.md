# Interpreter
Interpreter for my C-like programming language written on C++


## Language 
This is a C-family language. In fact, it can be described as C++ without many things. You can find its formal description [here](https://github.com/afentev/Interpreter/blob/main/name.docx).
### Types 
* ___integers___

  Integers are defined as "int". They are stored in signed 32-bit integers in C++. Now integers support all operators as in C++ with the exception of inversion and unary "+" and "-". I am going to add them a little bit later.
* ___doubles___

  Doubles are defined as "double". They are stored in C++ long double type. They also support all C++ operators such as summation, multiplication, or division.

* ___strings___
 
  Now the string is the most useless type in the language. It can only be concatenated. There is no access by index or something. I think I'll do it later.

* ___arrays___
  
  Unfortunately, arrays are absent in the interpreter now. Only syntax analyzer allows "vectors" and all other parts of the interpreter will ignore arrays in the best case.

### Operators
 This is the table with all operators and their priorities:
 
 Operator  | Priority
------------- | -------------
=, +=, -=, *=, /=, %=, \|=, &=, ^=  | 1
\|\| | 2
&& | 3
\| | 4
^ | 5
& | 6
==, != | 7
<, <=, >, >= | 8
\>>, << | 9
+, - | 10
*, /, %, // | 11
** | 12
++, --, !, ~, + (un), - (un) | 13
. (member access) | 14
[ ] (index access) | 15

### Functions
This language allows you to create functions. All function declarations must begin with the _fn_ keyword with the following type designation. There are no void functions. The interpreter does not control the number of provided arguments with function call so this is a dangerous part.

At this moment there is no recursion in my language. This is also because of several complications in the interpreter. 

## Interpreter
The interpreter consists of several parts: Token separator, Syntax analyzer, Semantic analyzer, and Generator. 

### Token separator
The token separator is located in the ["lexic_analyzer.h"](https://github.com/afentev/Interpreter/blob/main/lexic_analyzer.h) file. As input, it receives program code and as output, it returns an array of tokens and their generalized types.

### Syntax analyzer
The syntax analyzer is located in the ["syntax_analyzer.h"](https://github.com/afentev/Interpreter/blob/main/syntax_analyzer.h) file. Syntax analyzer is used for checking if the given program code belongs to the language. It checks only the nonexistence of unrecognized tokens and the correctness of recognized tokens correction.
I noticed that there are several problems with it. More specifically, it seems like they are connected with functions in some ways. This part needs to be improved.

### Semantic analyzer
The semantic analyzer is located in the ["semantic_analyzer.h"](https://github.com/afentev/Interpreter/blob/main/semantic_analyzer.h) file. Personally, I think that semantic analyzer now is a kinda useless part of an interpreter. It was planned as a part of the interpreter which would check the correctness of variables using and types consistency. But there were a lot of problems with all these checks so I decided just to turn off this analyzer. All its functions exist in the Generator, so all semantics problems are caught but in runtime.

### Generator
The Generator located in the ["generation.h"](https://github.com/afentev/Interpreter/blob/main/generation.h) file. The Generator consists of the actual generator and the executor. 
The generator creates a Polish Recersed Notation of the program (strictly speaking of each function) and the executor executes it.


# Example:
## Input:

```rust
fn int factorial(int x) {
    int ans = 1;
    for (int i = 1; i <= x; ++i) {
        ans *= i;
    }
    return ans;
}

fn int factorize(int x) {
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            print(i);
            print(" ");
        }
    }
    print("\n");
}

fn int fibonacci(int n) {
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 1;
    } else {
        int a = 1;
        int b = 1;
        for (int i = 0; i < n - 2; ++i) {
            a += b;
            b = a - b;
        }
        return a;
    }
}

fn int loops() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int k = 1;
            while (k < 10) {
                print(i);
                print(" ");
                print(j);
                print(" ");
                print(k);
                print("\n");
                k++;
            }
        }
    }
    print("\n");
    print("\n");
    return 0;
}

fn double ternSearch() {
    double lhs = 0 - 12;
    double rhs = 16;
    double mid;
    while (rhs - lhs > 0.00001) {
        mid = (rhs + lhs) / 2;
        if (mid * mid * mid > 0) {
            rhs = mid;
        } else {
            lhs = mid;
        }
    }
    print(rhs)
    print("\n");
    print(rhs * rhs * rhs);
    print("\n");
    return 0;
}

fn int main() {
    print(factorial(6));
    print("\n");
    factorize(120);
    print(fibonacci(5));
    print("\n");
    #loops();
    ternSearch();
    return 0;
}
```

## Output:
```
720
1 2 3 4 5 6 8 10 
5
9.5367431640625e-07
8.673617379884035e-19
```

And the main's RPN is:
```
6 factorial print \n print 120 factorize 5 fibonacci print \n print ternSearch 0 return
```

For example, this is the RPN of fibonacci function:
```
&5 &5 1 == @10 !? 1 return @53 !! &5 2 == @19 !? 1 return @53 !! &6 1 = &7 1 = &8 0 = &8 &5 2 - < @51 !? @41 !! &8 ++ @28 !! &6 &7 += &7 &6 &7 - = @37 !! &6 return
```

