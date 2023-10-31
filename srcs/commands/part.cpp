#include "../../include/Server.hpp"

//	PART #test
//	:KullaniciAdi!KullaniciHostName PART #KanalAdi

void	Server::part_command( Client &client )
{
	commandMsg(client, "PART");
	std::string msg;
	int targetChn = GetChannelFromName(inputs[1]);
	if (inputs.empty() || inputs.size() < 2)
	{
		msg = getprefix(client) + " " + ERR_NEEDMOREPARAMS(client.nickName, "PART") + "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Part", 0);
		return;
	}

	if (targetChn < 0)
	{
		msg = getprefix(client) + " " + ERR_NOSUCHCHANNEL(client.nickName, "PART") + "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Part", 0);
		return;
	}

	if (!channels[targetChn].isClientHere(client.nickName))
	{
		std::cout << "IRC: Client is joined this channel.\n";
		msg = getprefix(client) + " " + ERR_NOTONCHANNEL(client.nickName, "PART") + "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Part", 0);
		return;
	}
	msg = getprefix(client) + " PART " + channels[targetChn].chnName + " :" + RPL_PART(getprefix(client), channels[targetChn].chnName) + "\r\n";
	channels[targetChn].brodcastMsg(msg);
	msg = getprefix(client) + " PART " + inputs[1];
	execute(send(client.fd, msg.c_str(), msg.length(), 0), "Part", 0);
	channels[targetChn].eraseClient(client.nickName);
	if(channels[targetChn].chnClientsNum < 1)
		channels.erase(channels.begin() + targetChn);
}
