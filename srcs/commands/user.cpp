#include "../../include/Server.hpp"

void Server::user_command(Client &client)
{
	std::cout << "IRC: Called USER command\n";
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
				client._userName = *it;
			}
			else if ((*it)[0] == ':')
			{
				client._host = *it2;
				break;
			}
			else
			{
				it++;
				it2++;
			}
		}
		std::string msg = "Welcome to irc server!\n";
		send(client.fd, msg.c_str(), msg.length(), 0);
	}
	else
	{
		std::string msg = "ERROR!\n";
		send(client.fd, msg.c_str(), msg.length(), 0);
		msg.clear();
	}
}
