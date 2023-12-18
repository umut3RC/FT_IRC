#include "../../include/Server.hpp"

void	Server::nick_command( Client &client )
{
	std::string msg;
	commandMsg(client, "NICK");
	if (inputs.size() < 2)
	{
		msg = ERR_NONICKNAMEGIVEN(client.nickName);
		std::cout << "IRC: " << msg << '\n';
		msg += "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "NICK", 0);
		return;
	}
	int	targetFd = GetClientFdFromName(inputs[1], client.fd);
	if (targetFd > 0)
	{
		std::cout << "IRC: Nick is already used!\n";
		msg = ERRnickNameINUSE(client.nickName);
		msg += "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Nick", 0);
		return;
	}
	if ((int)inputs.size() > 3)
	{
		unsigned long int i = 0;
		while (i < inputs.size())
		{
			if (inputs[i] == "NICK")
				client.nickName = inputs[i + 1];
			if (inputs[i] == "USER")
				client.userName = inputs[i + 1];
			else if (inputs[i][0] == ':')
				client.host = inputs[i - 1];
			i++;
		}
	}
	else
	{
		msg = getprefix(client);
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Nick", 0);
		for (unsigned long int k = 0; k < channels.size(); k++)
		{
			if (channels[k].isOperator(client.nickName))
			{
				if (channels[k].isOperator(client.nickName))
				{
					for (int j = 0; j < (int)channels[k].chnOperators.size(); j++)
					{
						if (channels[k].chnOperators[j] == client.nickName)
						{
							channels[k].chnOperators[j] = inputs[1];
							break;
						}
					}
				}
			}
			for (unsigned long int j = 0; j < channels[k].whiteList.size(); j++)
			{
				if (channels[k].whiteList[j] == client.nickName)
				{
					channels[k].whiteList[j] = inputs[1];
					break;
				}
			}
			for (unsigned long int j = 0; j < channels[k].chnClients.size(); j++)
			{
				if (channels[k].chnClients[j].nickName == client.nickName)
				{
					channels[k].chnClients[j].nickName = inputs[1];
					break;
				}
			}
		}
		client.nickName = inputs[1];
	}
}
