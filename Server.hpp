#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include "utils.hpp"
class Server
{
	private:
		int	_port;
		int	_passwd;
		int	_sockfd;
		int	_svclientnum;
		int	_chnum;
		char	buffer[1024];
	public:
		Server( char **av );
		~Server( void );
		Server( const Server &src );

		Server &operator=( const Server &src);

};

#endif