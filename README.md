# Operating Systems Project
    A simple Linux shell implementation using UNIX commands and C

## Functionality outline:
The shell has following capabilities:

- count how many characters are in the file
- count how many words are in the file
- count how many lines are in the file
- count number of occurence of specific character/word given as parameter
- format text in a camel case manner
- convert text to all lowercase
- convert text to all upper case

The user can select any of the functions and provide a file name, after which the shell will return the result. The shell will countinue displaying a prompt until "exit" is typed in.

Count functions were implemented by using UNIX command and the execvp() system call, which is encapsulated in the executeCommand() method within the program, while format functions were implemented using C code and file I/O.

## Instructions
Inside the terminal, use gcc to compile the shell.c file (no particular flags are needed) and then run it. The rest of the instructions will be printed as a part of the shell.



