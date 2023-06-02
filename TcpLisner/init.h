#pragma once

#ifndef INIT_H
#define INIT_H

#include <fstream>
#include <winsock2.h>
#include <iostream>
#include <vector>
#include <ws2tcpip.h>
#include <thread>
#include <string>

// Internal utils includes 
#include "logger.h"
#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE 4096

void init();

#endif // INIT_H
