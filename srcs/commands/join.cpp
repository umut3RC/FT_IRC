#include "../../include/Server.hpp"

//JOIN #Oda_adi PASS

int	Server::findChannel( void )
{
	int	index = -1;
	if (inputs.size() < 2)
		return(index);
	for (int i = 0 ; i < (int)channels.size(); i++)
	{
		if (inputs[1] == channels[i].chnName)
		{
			index = i;
			return (index);
		}
	}
	return (index);
}
void	Server::createNewChannel(Client &client)
{
	std::string msg = getprefix(client);
	Channel newChannel(inputs[1]);
	if (inputs.size() == 2)
		newChannel.chnPass = inputs[2];
	newChannel.chnClients.push_back(client);
	newChannel.chnClientsNum++;
	newChannel.chnOperators.push_back(client.nickName);
	newChannel.hasPass = false;
	newChannel.modeN = false;
	newChannel.modeI = false;
	channels.push_back(newChannel);
	serverChnNum++;
	msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
	execute(send(client.fd, msg.c_str(), msg.length(), 0), "Create New Channel", 1);
	msg.clear();
	std::cout << "IRC: New Channel created.\n";
}

void	Server::join_command( Client &client )
{
	commandMsg(client, "JOIN");
	int	index;
	std::string msg = getprefix(client);
	index = findChannel();
	if (inputs[1][0] != '#')
		inputs[1] = '#' + inputs[1];
	inputs[1] = strCleaner(inputs[1]);
	if (index > -1)
	{
		if (channels[index].hasPass)
		{
			if (inputs.size() < 3)
			{
				msg = ERR_NEEDMOREPARAMS(getprefix(client), "Join");
				msg += "\r\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
			}
			if (strncmp(inputs[2].c_str(), channels[index].chnPass.c_str(), channels[index].chnPass.length()))
			{
				std::cout << "IRC: Channel has pass\n"; 
				msg = ERR_PASSWDMISMATCH(client.nickName);
				msg += "\r\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
				msg.clear();
				return;
			}
		}
		if (channels[index].maxUser == channels[index].chnClientsNum)
		{
			msg = ERR_CHANNELISFULL(getprefix(client), inputs[1]);
			msg += "\r\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
			return;
		}
		if (channels[index].modeI == true)
		{
			if (channels[index].whiteList.empty())
			{
				std::cout << "IRC: White List is empty!\n";
				msg = ERR_INVITEONLYCHAN(inputs[1]);
				msg += "\r\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
				return;
			}
			for (unsigned long int l = 0; l < channels[index].whiteList.size(); l++)
			{
				if (channels[index].whiteList[l] == client.nickName)
				{
					channels[index].chnClients.push_back(client);
					channels[index].chnClientsNum++;
					msg = msg + ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
					for (int j = 0; j < channels[index].chnClientsNum; j++)
					{
						execute(send(channels[index].chnClients[j].fd, msg.c_str(), msg.length(), 0), "Join", 0);
					}
					return;
				}
			}
			std::cout << "IRC: You are not invited!\n";
			msg = ERR_INVITEONLYCHAN(inputs[1]);
			msg += "\r\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
			return;
		}
		channels[index].chnClients.push_back(client);
		channels[index].chnClientsNum++;
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		for (int j = 0; j < channels[index].chnClientsNum; j++)
		{
			execute(send(channels[index].chnClients[j].fd, msg.c_str(), msg.length(), 0), "Join", 0);
		}
		return;
	}
	else
		createNewChannel(client);
}
