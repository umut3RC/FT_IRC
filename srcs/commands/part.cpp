#include "../../include/Server.hpp"

//	PART #test
//	:KullaniciAdi!KullaniciHostName PART #KanalAdi

// void	Server::part_command( Client &client )
// {
// 	commandMsg(client, "PART");
	
// 	int	targetChn = GetChannelFromName(inputs[1]);
// 	std::string	msg;
// 	if (targetChn < 0)
// 	{
// 		std::cout << "IRC: You need to join a channel!\n";
// 		return;
// 	}
// 	msg = getprefix(client) + " PART " + inputs[1] + "\r\n";
// 	send(client.fd, msg.c_str(), sizeof(msg.c_str()), 0);
// }

// void    Server::broadcastPart(const std::vector<Client *> &clientList, std::string msg, int excludeFd, std::string channelName) {
//     for (size_t i = 0; i < clientList.size(); i++)
//     {
//         if (clientList[i]->getFd() == excludeFd)
//             continue ;
//         ft_write(clientList[i]->getFd(), ":" + _clients[excludeFd]->getPrefixName() + " PART " + channelName + " :" + msg);
//     }
// }

void	Server::part_command( Client &client )
{
	commandMsg(client, "PART");
	std::string msg;
	int targetChn = GetChannelFromName(inputs[1]);
	if (inputs.empty() or inputs.size() < 2) {
		msg = getprefix(client) + " " + ERR_NEEDMOREPARAMS(client.nickName, "PART") + "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "ERR\n");
		return;
	}

	if (targetChn < 0)
	{
		msg = getprefix(client) + " " + ERR_NOSUCHCHANNEL(client.nickName, "PART") + "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "ERR\n");
		return;
	}

	if (!channels[targetChn].isClientHere(client.nickName))
	{
		std::cout << "IRC: Client is joined this channel.\n";
		msg = getprefix(client) + " " + ERR_NOTONCHANNEL(client.nickName, "PART") + "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "ERR\n");
		return;
	}
	// broadcastPart(channel->_channelClients , RPL_PART(_clients[fd]->getPrefixName(), channels[targetChn].name), fd, inputs[1]);
	msg = getprefix(client) + " PART " + channels[targetChn].chnName + " :" + RPL_PART(getprefix(client), channels[targetChn].chnName) + "\r\n";
	// for (int i = 0; i < (int)channels[targetChn].chnClients.size(); i++)
	// {
	// 	if (channels[targetChn].chnClients[i].nickName != client.nickName)
	// 		execute(send(channels[targetChn].chnClients[i].fd, msg.c_str(), msg.length(), 0), "ERR\n");
	// }
	channels[targetChn].brodcastMsg(msg);
	msg = getprefix(client) + " PART " + inputs[1];
	execute(send(client.fd, msg.c_str(), msg.length(), 0), "ERR\n");
	channels[targetChn].eraseClient(client.nickName);
	// if (_clients[fd]->_channels[i]->getClientCount() == 0)
	// {
	// 	std::cout << _clients[fd]->_channels[i]->getName() << " Channel delete...\n";
	// 	_channels.erase(_clients[fd]->_channels[i]->getName());
	// }
}
