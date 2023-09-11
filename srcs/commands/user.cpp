#include "../../include/Server.hpp"

void Server::user_command(Client &client)
{
	std::string msg;

	if (inputs.size() != 5)
	{
		msg = ":" + getprefix(client) + " 461 " + client._nickName + " USER :Not enough parameters";
		send(client.fd, msg.c_str(), msg.length(), 0);
		return;
	}
	client._userName = inputs[1];
	client._host = inputs[2];
	// _clients[fd]->setUserName(token[1]);
	// _clients[fd]->setRealName(token[4].substr(token[4][0] == ':', token[4].size()));
	msg = ":"  +getprefix(client) + " 001 " + client._nickName + " :Welcome to IRC";
	send(client.fd, msg.c_str(), msg.length(), 0);
}
