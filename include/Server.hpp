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
		std::vector<std::string>				inputs;
		std::vector<Client>						clients;
		std::vector<pollfd>						pollFd;
		std::vector<Channel>					channels;
		std::map<std::string, void(Server::*)(Client &client)> commands;
		struct sockaddr_in						_sockAddr;

		void	Poll( void );
		void	loop( void );
		void	commandHandler( void );
		void	runCommand(Client &client);
		void	setCommands( void );

		std::string	getprefix(Client &client);

		//Commands
		void	quit_command(Client &client);
		void	cap_command(Client &client);
		void	user_command(Client &client);
		void	join_command( Client &client );

		Server( char **av );
		~Server( void );
		Server( const Server &src );
		void sstart( void );

		Server &operator=( const Server &src);
};

#endif
