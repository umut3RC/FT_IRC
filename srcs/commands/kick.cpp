#include "../../include/Server.hpp"

///KICK #kanal kullanici_adi [sebep]
//:kanal_op!kanal_op@irc.sunucu.com KICK #kanal kullanici_adi :neden
void	Server::kick_command( Client &client )
{
	commandMsg(client, "KICK");
	std::string	msg;
	int	targetChn;

	msg = getprefix(client) + " " + inputs[0] + " " + inputs[1] + " " + inputs[2] + " :" + inputs[3] + "\n";
	targetChn = GetChannelFromName(inputs[1]);
	if(channels[targetChn].isOperator(client.nickName))
	{
		if (client.nickName != inputs[2] || channels[targetChn].isOperator(inputs[2]))
		{
			channels[targetChn].brodcastMsg(msg);
			channels[targetChn].eraseClient(msg);
		}
		else
			std::cout << "IRC: You can't kick an Operator!\n";
	}
	else
		throw std::runtime_error(ERR_CHANOPRIVSNEEDED(client.nickName, channels[targetChn].chnName));
}