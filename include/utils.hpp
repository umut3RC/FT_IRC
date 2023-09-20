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
#include <functional>
#include <algorithm> // std::transform
#include <cctype>	// std::toupper
#include <string>
#include <cstring>
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define ERR_NEEDMOREPARAMS(prefix, command) "461 " + prefix + " " +  command + " :Not enough parameters"

std::vector<std::string> splitString(const std::string& input, char delimiter);
void	ToLower(std::string &s);
void	ToUpper(std::string &s);
void	signalHandler( int s );
void	execute(int ret, std::string err);

#endif