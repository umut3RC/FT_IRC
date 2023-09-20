#include "../../include/Server.hpp"

void	Server::quit_command(Client &client)
{
	std::vector<Client>::iterator it;

	std::cout << "IRC: Called QUIT command\n";
	for (unsigned long int i = 0; i < channels.size(); i++)
	{
		for (unsigned long int j = 0 ; j < channels[i].chnclients.size(); j++)
		{
			if (channels[i].chnclients[j]._nickName == client._nickName)
			{
				if (channels[i]._admin == client._nickName)
				{
					std::cout << channels[i]._admin << '\n';
					it = channels[i].chnclients.begin() + i;
					it++;
					channels[i]._admin = it->_nickName;
					std::cout << channels[i]._admin << '\n';
				}
				channels[i].chnclients.erase(channels[i].chnclients.begin() + i);
				channels[i]._clientnum--;
				if (channels[i].chnclients.size() == 0)
					channels.erase(channels.begin() + i);
			}
		}	
	}

	for (unsigned long int i = 0 ; i < pollFd.size() ; i++)
	{
		if (client.fd == pollFd[i].fd)
		{
			std::string msg = ":" + getprefix(client) + " QUIT: Leaving " + inputs[inputs.size() - 1] + "\n";
			send(client.fd, msg.c_str(), msg.length(), 0);
			close(pollFd[i].fd);
			pollFd.erase(pollFd.begin() + i);
			break;
		}
	}

	for (int i = 0; i < _srvClientNum; i++)
	{
		if (clients[i]._nickName == client._nickName){
			std::vector<Client>::iterator it;
			it = clients.begin() + i;
			std::cout << it->_nickName << '\n';
			clients.erase(clients.begin() + i);
			_srvClientNum--;
		}
	}
	return;
}
