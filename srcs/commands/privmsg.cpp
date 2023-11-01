#include "../../include/Server.hpp"

/*
target user
message
message
message
...
*/
void Server::privmsg_command(Client &client)
{
	commandMsg(client, "PRIVMSG");
	std::string	msg = getprefix(client);
	std::string	targetName = inputs[1];
	int	targetFd = GetClientFdFromName(inputs[1], client.fd);
	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
	if (inputs.size() < 2)
	{
		msg = ERR_NEEDMOREPARAMS(getprefix(client), "Join");
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
		return;
	}
	for (unsigned long int i = 2; i < inputs.size(); i++)
	{
		msg = msg + inputs[i];
		msg = msg + ' ';
	}
	msg += "\r\n";
	if (inputs[1][0] == '#')
	{
		targetFd = GetChannelFromName(targetName);
		if (targetFd < 0)
		{
			return;
		}
		if (channels[targetFd].modeN)
		{
			for(unsigned long int l = 0; l < channels[targetFd].chnClients.size(); l++)
			{
				if (channels[targetFd].chnClients[l].nickName == client.nickName)
				{
					for (int k = 0; k < channels[targetFd].chnClientsNum; k++)
					{
						if (channels[targetFd].chnClients[k].nickName != client.nickName)
							execute(send(channels[targetFd].chnClients[k].fd, msg.c_str(), msg.length(), 0), "Privmsg", 0);
					}
					return;
				}
			}
			msg = msg +  " " + ERR_NOTONCHANNEL(client.nickName, inputs[1]) + "\r\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Privmsg", 0);
			return ;
		}
		else if (targetFd > -1)
		{
			std::cout << "IRC: Sended to clients on "<< inputs[1] <<" channel.\n";
			for (int k = 0; k < channels[targetFd].chnClientsNum; k++)
			{
				if (channels[targetFd].chnClients[k].nickName != client.nickName)
					execute(send(channels[targetFd].chnClients[k].fd, msg.c_str(), msg.length(), 0), "Privmsg", 0);
			}
		}
	}
	else
	{
		if (targetFd > -1)
			execute(send(targetFd, msg.c_str(), msg.length(), 0), "Privmsg", 0);
	}
}
