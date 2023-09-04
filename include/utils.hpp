#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream> //cout, cin, cerr
#include <sys/socket.h> // socket, setsockopt, getsockname, bind, connect, listen, accept, send, recv
#include <unistd.h> // close
#include <netdb.h> // getprotobyname, gethostbyname, freeaddrinfo, getaddrinfo
#include <arpa/inet.h> // htonl, htons, ntohs, ntohl, inet_addr, inet_ntoa,
#include <signal.h> // signal
#include <fcntl.h> // lseek, fstat, fcntl
#include <poll.h> // poll
#include <netinet/in.h> // struct sockaddr_in
#include <vector>
#include <map>
#include <algorithm> // std::transform
#include <cctype>    // std::toupper
#include <string>
#include <cstring>

std::vector<std::string> splitString(const std::string& input, char delimiter);
void	checkServerCommands(std::string cmd);
void	signalHandler( int s );

#endif