# Project Name
Implementation a Unix Shell in C

---

### Table of Contents

- [Description](#description)
- [How To Run](#how-to-run)
- [How to Use](#how-to-use)
- [Credits](#credits)

---
## Description

This project implements a unix shell. The use of the system() function is forbidden and wasn't used. The commands are executed with exec() family. This program manages zombie processes. This shell executes

- simple commands like "ls", "ps" etc.
    1) reading the file that is going to be executable from the terminal
    2) waiting until the new process will be terminated
    3) when the new process is terminated, terminal read and executes the next process 
- commands with flags such as "ls -l/home/user/"
- commands for input and output redirection from or to files. Also, overwrite > and appent >> are supported. For example, shell can execute the command
```
    $ cat < in.txt > out.txt
    $ cat < in.txt >> out.txt
```
- commands in pipe such as
```
    $ ls -l | wc -l > out.txt
```

## How to Run

 To run the source file:

1)Make sure that you are on the wright directory in your filesystem 
2) Open terminal and run the following command to run the program.


```
    $ ./myshell
```

## How To Use

Once the user run the program, the prompt symbol ($) will appear on display and will be waiting from user to give it a command. Once it executes the command, output will be displayed (depends on command). After the command execution, terminal is waiting the next command.

Program handles errors such as fork errors, exec errors, pipe errors, file open errors, process return errors etc.

## Credits

This is a teammate project. Special thanks to my teammate (https://github.com/Mhintirog
)

## Author info 

- E-mail - marith.zap@gmail.com

[Back to the top](#project-name)
