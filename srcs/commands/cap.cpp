#include "../../include/Server.hpp"

void	Server::cap_command(Client &client)
{
	commandMsg(client, "CAP");
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
			client.host = *it;
		}
		else if ((*it)[0] == ':')
		{
			client.host = *it2;
			break;
		}
		else{
			it++;
			it2++;
		}
	}
}