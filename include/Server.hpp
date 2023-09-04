#ifndef SERVER_HPP
# define SERVER_HPP

#include "utils.hpp"
#include "Client.hpp"

class Server
{
	public:
		int	_port;
		int	_passwd;
		int	_sockfd;
		int	_svclientnum;
		int	_chnum;

		Client	client;
		sockaddr_in	_sockAddr;
		char	buffer[1024];

		Server( char **av );
		~Server( void );
		Server( const Server &src );
		void sstart( void );

		Server &operator=( const Server &src);

};

#endif
