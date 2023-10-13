#include "../../include/Server.hpp"

void Server::user_command(Client &client)
{
	commandMsg(client, "USER");
	// std::string msg = ":" + getprefix(client) + " " + "001 Welcome\r\n";
	// send(client.fd, msg.c_str(), msg.size(), 0);
	if (inputs.size() > 5)
	{
		std::vector<std::string>::iterator it = inputs.begin();
		std::vector<std::string>::iterator it2;
		it2 = it;
		it++;

		while (it != inputs.end())
		{
			if (*it == "USER")
			{
				it++;
				it2++;
				client.userName = *it;
			}
			else if ((*it)[0] == ':')
			{
				client.host = *it2;
				break;
			}
			else
			{
				it++;
				it2++;
			}
		}
		// std::string msg = getprefix(client) + " 001 " + client.nickName + " :Welcome to ircserv";
		// execute(send(client.fd, msg.c_str(), sizeof(msg.c_str()), 0), "ERR\n");
	}
	else
	{
		std::string msg = "ERROR!\n";
		send(client.fd, msg.c_str(), msg.length(), 0);
		msg.clear();
	}
}
