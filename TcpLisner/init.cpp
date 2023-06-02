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

#pragma comment(lib, "ws2_32.lib")
#define MAX_BUFFER_SIZE 4096

using namespace std;


void init() {

    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    // Initialize Winsock
    int wsResult = WSAStartup(ver, &wsData);
    if (wsResult != 0) {
        cerr << "Can't initialize Winsock! Quitting..." << endl;
        Log("Can't initialize Winsock! Quitting...");
    }

    
}