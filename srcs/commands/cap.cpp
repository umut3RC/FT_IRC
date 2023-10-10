#include "../../include/Server.hpp"

void	Server::cap_command(Client &client)
{
	commandMsg(client, "CAP");
}