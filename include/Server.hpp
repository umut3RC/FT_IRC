#ifndef SERVER_HPP
# define SERVER_HPP

#include "utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"


class Server
{
	public:
		int	serverPort;
		int	serverSockFd;
		int	serverChnNum;
		int	serverClntNum;
		char	buffer[1024];
		std::string	serverPass;
		struct sockaddr_in						serverAddr;
		std::vector<std::string>				inputs;
		std::vector<Client>						clients;
		std::vector<pollfd>						pollFd;
		std::vector<Channel>					channels;
		std::map<std::string, void(Server::*)(Client &client)> commands;

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
		void	ping_command(Client &client);
		void	join_command( Client &client );
		void	nick_command( Client &client );
		void	mode_command( Client &client );
		void	pass_command( Client &client );
		void	privmsg_command( Client &client );
		void	part_command( Client &client );
		void	notice_command( Client &client );
		void	whois_command( Client &client );
		void	kick_command( Client &client );
		void	invite_command( Client &client );

		int	findChannel( void );
		int	GetClientFdFromName(std::string targetName, int fd);
		int	addNewClient(pollfd pfd, Client client, int clientSockFd);
		int	GetChannelFromName(std::string targetName);
		int	GetClientIndexFromName(std::string target);
		int	findMe(Client &client);
		bool	clientAuthentication(Client &client);
		void	printInputs( void );
		void	commandMsg(Client client, std::string comd);
		void	createNewChannel(Client &client);
		Server( char **av );
		~Server( void );
		Server( const Server &src );
		void sstart( void );

		Server &operator=( const Server &src);
};

#endif
