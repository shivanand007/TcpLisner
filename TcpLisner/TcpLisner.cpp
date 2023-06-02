#include <fstream>
#include <winsock2.h>
#include <iostream>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <string>

// Internal utils includes 
#include "logger.h"
#include "init.h"
#pragma comment(lib, "ws2_32.lib")
#define MAX_BUFFER_SIZE 4096

using namespace std;

int main()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    // Initialize Winsock
    int wsResult = WSAStartup(ver, &wsData);
    if (wsResult != 0) {
        cerr << "Can't initialize Winsock! Quitting..." << endl;
        Log("Can't initialize Winsock! Quitting...");
        return 1;
    }

    // Create a socket for each port you want to connect to
    SOCKET clientSockets[3];
    for (int i = 0; i < 3; ++i) {
        clientSockets[i] = socket(AF_INET, SOCK_STREAM, 0);

        if (clientSockets[i] == INVALID_SOCKET) {
            cerr << "Can't create a socket! Quitting..." << endl;
            Log("Can't create a socket! Quitting...");
            WSACleanup();
            return 1;
        }

        Log("Socket creation successful");
        cout << "Socket creation successful for port " << 3000 + i << endl;

        // Binding server address to each socket port
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(3000 + i);
        inet_pton(AF_INET, "172.18.80.112", &(serverAddress.sin_addr));

        if (connect(clientSockets[i], (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
            cerr << "Can't connect to the server on port " << 3000 + i << "! Quitting..." << endl;
            Sleep(500);
            cout << "Closing socket connection" << endl;
            closesocket(clientSockets[i]);
            WSACleanup();
            return 1;
        }

        cout << "Connected to the server on port " << 3000 + i << endl;
        string msg = "Connected to the server on port " + to_string(3000 + i);
        Log(msg);
    }

    // Receive welcome message from the server
    while (true) {

        for (int i = 0; i < 3; ++i) {
    
            char buffer[MAX_BUFFER_SIZE];
            memset(buffer, 0, MAX_BUFFER_SIZE);

            // Receive data from the server
            int bytesReceived = recv(clientSockets[i], buffer, MAX_BUFFER_SIZE - 1, 0);

            if (bytesReceived > 0 && bytesReceived < MAX_BUFFER_SIZE) {
                buffer[bytesReceived] = '\0'; // Add null-terminator
                string message = "Server on port " + to_string(3000 + i) + " says: " + buffer;
                cout << message << endl;
                Log(message);
            }
            else if (bytesReceived == 0) {
                // Connection closed by the server
                cout << "Connection closed by the server on port " << 3000 + i << endl;
                break;
            }
            else {
                // Error occurred while receiving data
                cerr << "Error receiving data from the server on port " << 3000 + i << "! Quitting..." << endl;
                Log("Error receiving data from the server on port " + to_string(3000 + i));
                break;
            }
        }
    }

    // Clean up
    for (int i = 0; i < 3; ++i) {
        closesocket(clientSockets[i]);
    }

    WSACleanup();

    return 0;
}
