#include "../../include/Server.hpp"

void Server::privmsg_command(Client &client)
{
	std::cout << "IRC: PRIVMSG USER command\n";
	(void)client;
}
