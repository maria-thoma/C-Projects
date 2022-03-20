# Project Name
multithread CLient- Server Calculator using TCP/IP communication protocol
---

### Table of Contents

- [Description](#description)
- [How To Run](#how-to-run)
- [How to Use](#how-to-use)
- [Credits](#credits)

---
## Description

This project implements a multithread server- client calculator using the TCP/IP protocol. It contains server's and client's source file. Server can handle and serve many clients at the same time. A client conects to server and sents a simple arithmetic operation. Server calculates the operation and sents it back to the client. Server runs locally in your computer using the localhost (127.0.0.1).

## How to Run

 To run the source file:

1)Make sure that you are on the wright directory in your filesystem 
2)Open terminal and run the following command to start running the server. Note in port argument to use a free port that isn't assigned to any other server.


```
    $ ./server port
```
3)Open another terminal to run the client. In port argument put the port where the server is listening
```
    $./client port 127.0.0.1
```
Note that a new terminal can be opened and another client established connection with server.

## How To Use

Once the server runs it listens at a particular port and waits for clients to connect. When a client connects to server, he can sent an arithmetic operation and get the answer from the server. This process can be done for many clients.


## Credits

This is a teammate project. Special thanks to my teammate (https://github.com/Mhintirog)

## Author info 

- E-mail - marith.zap@gmail.com

[Back to the top] (#project-name)

