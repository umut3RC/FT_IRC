#ifndef SERVER_HPP
# define SERVER_HPP

#include "utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Server
{
	public:
		int	_port;
		int	_passwd;
		int	_sockfd;
		int	_chNum;
		int	_srvClientNum;
		char	buffer[1024];
		std::vector<std::string>	inputs;
		std::vector<Client>			clients;
		std::vector<pollfd>			pollFd;
		std::vector<Channel>		channels;
		struct sockaddr_in			_sockAddr;

		void	quit(Client &client);
		void	Poll( void );
		void	loop( void );
		void	commandHandler( void );
		void	runCommand(Client &client);
		std::string	getprefix(Client &client);

		Server( char **av );
		~Server( void );
		Server( const Server &src );
		void sstart( void );

		Server &operator=( const Server &src);

};

#endif
