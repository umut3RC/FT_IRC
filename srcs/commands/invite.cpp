#include "../../include/Server.hpp"

// //	/INVITE hedef_kullanici #hedef_kanal
// //	:Sunucu_Adı INVITE Davet_Eden_Kullanıcı Davet_Edilen_Kullanıcı #Hedef_Kanal

void	Server::invite_command( Client &client )
{
	commandMsg(client, "INVITE");
	std::string	msg;
	if (inputs.size() < 3)
	{
		msg = ERR_NEEDMOREPARAMS(getprefix(client), "invite");
		msg += "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Invite", 0);
		return;
	}
	std::string	chn = inputs[2];
	int	targetFd;
	int	targetChn;
	msg = getprefix(client) + " INVITE " + client.nickName + " " + inputs[1] + " " + chn;
	targetFd = GetClientFdFromName(inputs[1], client.fd);
	if (targetFd < 0)
	{
		std::cout << "IRC: Client is not founded" << std::endl;
		return;
	} 
	targetChn = GetChannelFromName(chn);
	if (targetChn < 0)
	{
		std::cout << "IRC: Invalid channel room!\n";
		return;
	}
	if (!channels[targetChn].isOperator(client.nickName))
	{
		std::cout << "IRC: You are not an Operator!\n";
		return;
	}
	channels[targetChn].whiteList.push_back(inputs[1]);
	msg = "You have been invited to channel " + chn + " you can type /join to join that channel\r\n";
	execute(send(targetFd, msg.c_str(), msg.length(), 0), "Invite", 0);
}
