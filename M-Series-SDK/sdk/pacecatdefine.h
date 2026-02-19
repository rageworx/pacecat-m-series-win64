#ifndef __PACECATDEFINE_H__
#define __PACECATDEFINE_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef UNUSED
    #define UNUSED(x) (void)x
#endif /// of UNUSED

#ifdef _WIN32
    #ifndef NOMINMAX
                #define NOMINMAX
    #endif /// of NOMINMAX

    #include <io.h>			//for access
    #include <ws2tcpip.h>
    #include <winsock.h>
    #include <Windows.h>
    #include <iphlpapi.h>
#elif __unix__
    #include <sys/time.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <netinet/tcp.h>
    #include <sys/socket.h>
    #include <sys/wait.h>
    #include <arpa/inet.h>
    #include <stdarg.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include <termios.h>
    #include <sys/ioctl.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <dirent.h>
#endif
#endif /// of __PACECATDEFINE_H__
