#include "../../include/Server.hpp"

void	Server::quit_command(Client &client)
{
	commandMsg(client, "QUIT");

	std::vector<Client>::iterator it;
	std::vector<std::string>::iterator iter;
	for (unsigned long int i = 0; i < channels.size(); i++)
	{
		for (unsigned long int j = 0 ; j < channels[i].chnClients.size(); j++)
		{
			if (channels[i].chnClients[j].nickName == client.nickName)
			{
				iter = std::find(channels[i].chnOperators.begin(), channels[i].chnOperators.end(), client.nickName);
				if (iter != channels[i].chnOperators.end())
				{
					it = channels[i].chnClients.begin() + i;
					it++;
					iter = std::find(channels[i].chnOperators.begin(), channels[i].chnOperators.end(), client.nickName);
					channels[i].chnOperators.erase(iter);
					channels[i].chnOperators.push_back(it->nickName);
				}
				channels[i].chnClients.erase(channels[i].chnClients.begin() + i);
				channels[i].chnClientsNum--;
				if (channels[i].chnClients.size() == 0)
					channels.erase(channels.begin() + i);
			}
		}	
	}

	for (unsigned long int i = 0 ; i < pollFd.size() ; i++)
	{
		if (client.fd == pollFd[i].fd)
		{
			std::string msg = ":" + getprefix(client) + " QUIT: Leaving " + inputs[inputs.size() - 1] + "\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Quit", 0);
			close(pollFd[i].fd);
			pollFd.erase(pollFd.begin() + i);
			break;
		}
	}

	for (int i = 0; i < serverClntNum; i++)
	{
		if (clients[i].nickName == client.nickName)
		{
			it = clients.begin() + i;
			std::cout << it->nickName << '\n';
			clients.erase(clients.begin() + i);
			serverClntNum--;
		}
	}
	return;
}
