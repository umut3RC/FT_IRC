#include "../../include/Server.hpp"

void	Server::cap_command(Client &client)
{
	// std::cout << "IRC(" << client.nickName << " " << client.fd << "): CAP command\n";
	commandMsg(client, "CAP");
}