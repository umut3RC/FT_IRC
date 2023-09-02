#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream> //cout, cin, cerr
#include <sys/socket.h> // socket, setsockopt, getsockname, bind, connect, listen, accept, send, recv
#include <unistd.h> // close
#include <netdb.h> // getprotobyname, gethostbyname, freeaddrinfo, getaddrinfo
#include <arpa/inet.h> // htonl, htons, ntohs, ntohl, inet_addr, inet_ntoa,
#include <signal.h> // signal
#include <fcntl.h> // lseek, fstat, fcntl
#include <poll.h> // poll
#include <netinet/in.h> // struct sockaddr_in
/*containers*/
#include <algorithm>
#include <vector>
#include <map>
#include <unistd.h>
#include <algorithm> // std::transform
#include <cctype>    // std::toupper
#include <string>
#include <cstring>
#include "utils.hpp"

class Server
{
	public:
		int	_port;
		int	_passwd;
		int	_sockfd;
		int	_svclientnum;
		int	_chnum;
		char	buffer[1024];

		Server( char **av );
		~Server( void );
		Server( const Server &src );
		void sstart( void );

		Server &operator=( const Server &src);

};

#endif