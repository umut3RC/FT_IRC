#include "../../include/Server.hpp"

void	Server::ping_command(Client &client)
{
	commandMsg(client, "PING");
	if (inputs.size() > 1)
	{
		std::string msg;
		msg = getprefix(client) + " PONG :" + inputs[1] + "r\n";
		execute(send(client.fd, msg.c_str(), msg.size(), 0), "Ping", 0);
	}
}