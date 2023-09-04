#ifndef SERVER_HPP
# define SERVER_HPP

#include "utils.hpp"
#include "Client.hpp"

class Server
{
	public:
		Client client;
		int	_port;
		int	_passwd;
		int	_sockfd;
		sockaddr_in	_sockAddr;
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