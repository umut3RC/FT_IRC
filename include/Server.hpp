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
		int	_chNum;
		int	_svclientnum;
		
		char	buffer[1024];

		std::vector<Client>	clients;
		std::vector<pollfd>	pollFd;
		struct sockaddr_in	_sockAddr;

		void Poll( void );
		int Hexchat( void );
		Server( char **av );
		~Server( void );
		Server( const Server &src );
		void sstart( void );

		Server &operator=( const Server &src);

};

#endif
