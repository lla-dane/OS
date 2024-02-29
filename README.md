# DNS Service

## Description

This project implements a simple, multithreaded naming service using Java sockets. It consists of two main components: a server and a client. The server listens on port 6052 for client connections, resolves the requested IP names to IP addresses, and returns the result. Initially, the server can be tested using telnet, allowing for easy debugging before a dedicated client application is used.

## Prerequisites

- Java JDK 11 or later
- Basic knowledge of Java programming
- Understanding of network sockets and multithreading in Java

## Installation

1. Clone the repository to your local machine:

```bash
git clone <repository-name> 
```

2. Navigate to the cloned directory:


3. Compile the server and client code in separate terminals:

```bash
javac server.java
javac client.java
```


## Usage

### Starting the Server

Run the server application using the Java interpreter:

```bash
java server
```

The server will start and listen on port 6052 for incoming connections.

### Testing with Telnet

Before using the custom client, you can test the server functionality with telnet in a separate terminal while the server is running:

```bash
telnet localhost 6052
```

After connecting, input the hostname you want to resolve, e.g., `www.example.com`, and press Enter. The server should respond with the IP address or an error message.

### Using the Client Application

Run the client application to resolve a hostname:

```bash
java client www.example.com
```
The client will connect to the server, send the hostname, and print the response from the server.






