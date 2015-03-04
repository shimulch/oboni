Oboni
=======

After getting so curious about how a interpreter works internally I decieded to develop my own interpreted language. And the result is oboni. I am still working on removing its bugs and add new features.

My current approch is so simple. Lexer -> Parser -> Interpret

For lexer and parser I didnt used any third party. All hand coded. As my intend is to learn in depth. The interpreter for Oboni is developed in C.

#Lexer

lexer.h and lexer.c, those are the files that working for lexical analysis. Also for regular expression I coded some finite state machines that can be found in fsm.h and fsm.c files.

#Parser

An Abstract Syntax Tree is getting build after getting token list from lexer. I tried to keep it simple. Grammers that are used for parser are-

EXPRESSION -> STATEMENT EXPRESSION_PRIME
            | CONTROLFLOW EXPRESSION_PRIME
            | EPSILON

EXPRESSION' -> STATEMENT '\n' EXPRESSION
             | CONTROLFLOW '\n' EXPRESSION
             | EPSILON
             
STATEMENT  -> var identifier
            | = identifier TERM
            | show TERM
            
CONTROLFLOW -> if '(' EVALUATION ')' BLOCK
             | when '(' EVALUATION ')' BLOCK
             
BLOCK -> '{' EXPRESSION_PRIME '}' EXPRESSION_PRIME

TERM  -> identifier
       | number
  		 | string
       | '(' EVALUATION ')'
       
EVALUATION  -> operator TERM TERM


As you guessed I tried to implement Polish prefix notation for equations or statements. Because it gave me somewhat relif for operator precedence checking.

So a simple Oboni program looks like this - 

var x
= x 1
when(< x 100){
  show x
  = x (+ x 1)
}

That show is currently just working like a keyword but I will move to functions when I will implement functions in my language.
