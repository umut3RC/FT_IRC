#include "../../include/Server.hpp"

void	Server::cap_command(Client &client)
{
	std::cout << "IRC: Called CAP command\n";
	(void)client;
}