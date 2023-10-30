#include "../../include/Server.hpp"

void Server::user_command(Client &client)
{
	commandMsg(client, "USER");
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
	}
	else
	{
		std::string msg = "ERROR!\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "User", 0);
		msg.clear();
	}
}
