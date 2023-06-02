# TcpLisner

TcpLisner is a C++ program that demonstrates TCP socket communication by connecting to multiple ports and receiving messages from a server. It uses the Winsock library for Windows systems.

## Features

- Connects to multiple ports on a server
- Receives messages from the server on each port
- Logs the received messages with timestamps in log files

## Requirements

- Windows operating system
- C++ compiler
- Winsock library

## Usage

1. Clone the repository or download the source code.
2. Build the project using a C++ compiler.
3. Run the executable file to connect to the server and receive messages on the specified ports.
4. Log files will be created in the "logs" directory, with each log file named as per the date.

## Configuration

You can modify the following settings in the code:

- Server IP address: Modify the IP address in the `inet_pton` function call to connect to your desired server.
- Port numbers: The program connects to ports 3000, 3001, and 3002 by default. Modify the port numbers in the `for` loop to connect to different ports.
- Log file size: The maximum size for each log file is set to 20MB. Modify the `maxFileSize` constant to adjust the file size limit.

## Contributing

Contributions to TcpLisner are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

