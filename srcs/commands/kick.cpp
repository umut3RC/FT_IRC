#include "../../include/Server.hpp"

///KICK #kanal kullanici_adi [sebep]
//:kanal_op!kanal_op@irc.sunucu.com KICK #kanal kullanici_adi :neden
void	Server::kick_command( Client &client )
{
	commandMsg(client, "KICK");
	std::string	msg;
	std::string ret = "(undefined)";
	int	targetChn;

	if (inputs.size() > 3)
	{
		ret = inputs[3];
		for (int i = 4; i < (int)inputs.size(); i++)
			ret += inputs[i];
	}
	msg = getprefix(client) + " " + inputs[0] + " " + inputs[1] + " " + inputs[2] + " :" + ret + "\r\n";
	targetChn = GetChannelFromName(inputs[1]);
	if (targetChn < 0)
	{
		msg = ERR_NOSUCHCHANNEL(getprefix(client), inputs[1]);
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Kick", 0);
	}
	else if(channels[targetChn].isOperator(client.nickName))
	{
		targetChn = GetClientFdFromName(inputs[2], client.fd);
		if (targetChn < 0)
		{
			msg = ERR_USERNOTINCHANNEL(getprefix(client), client.nickName, inputs[1]);
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Kick", 0);
		}
		std::vector<std::string>::iterator	whiteList_iter;
		whiteList_iter = std::find(channels[targetChn].whiteList.begin(), channels[targetChn].whiteList.end(), inputs[2]);
		if (whiteList_iter != channels[targetChn].whiteList.end())
			channels[targetChn].whiteList.erase(whiteList_iter);
		if (client.nickName != inputs[2] && !channels[targetChn].isOperator(inputs[2]))
		{
			channels[targetChn].brodcastMsg(msg);
			channels[targetChn].eraseClient(msg);
		}
		else
			std::cout << "IRC: You can't kick an Operator!\n";
	}
	else
	{
		msg = ERR_CHANOPRIVSNEEDED(getprefix(client), channels[targetChn].chnName);
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Kick", 0);
	}
}
