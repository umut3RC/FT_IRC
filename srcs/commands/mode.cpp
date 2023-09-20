#include "../../include/Server.hpp"

void	Server::mode_command( Client &client )
{
	std::cout << "IRC: Called MODE command\n";
	(void)client;
}