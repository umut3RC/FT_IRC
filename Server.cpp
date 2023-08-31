#include "Server.hpp"

Server::Server( char **av )
{
	_port = ft_atoi(av[1]);
	_passwd = ft_atoi(av[2]);
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	_svclientnum = 0;
	_chnum = 0;
	if (_sockfd == -1)
		throw ("Error!\nSocket could not be created!\n");
	else
		std::cout << "socket created successfully\n";
};

Server::Server( const Server &src )
{

}

Server::~Server( void )
{

}

Server &Server::operator=( const Server &src);
{
	
}