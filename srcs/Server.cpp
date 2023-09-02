#include "../include/Server.hpp"

Server::Server( char **av )
{
	std::cout << "Server starting . . .\n";
	_port = ft_atoi(av[1]);
	_passwd = ft_atoi(av[2]);
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	_svclientnum = 0;
	_chnum = 0;
	if (_sockfd == -1)
		throw ("Error!\nSocket could not be created!\n");
	else
		std::cout << "socket created successfully\n";
}

Server::Server( const Server &src )
{
	*this = src;
}

Server::~Server( void )
{
	std::cout << "Server closed. Have a good day!\n";
}
void Server::sstart( void )
{
	std::cout << "Server started.\n";
}

Server &Server::operator=( const Server &src)
{
	this->_port = src._port;
	this->_passwd = src._passwd;
	this->_sockfd = src._sockfd;
	this->_svclientnum = src._svclientnum;
	this->_chnum = src._chnum;
	return (*this);
}