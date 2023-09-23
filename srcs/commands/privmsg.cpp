#include "../../include/Server.hpp"

void Server::privmsg_command(Client &client)
{
	std::cout << "IRC: PRIVMSG USER command\n";
	for (int i = 0; i < (int)inputs.size();i++)
	{
		std::cout << "InPriv: " << inputs[i] << std::endl;
	}
	(void)client;
}
