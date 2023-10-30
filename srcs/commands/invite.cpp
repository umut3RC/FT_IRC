#include "../../include/Server.hpp"

//	/INVITE hedef_kullanici #hedef_kanal
//	:Sunucu_Adı INVITE Davet_Eden_Kullanıcı Davet_Edilen_Kullanıcı #Hedef_Kanal

void	Server::invite_command( Client &client )
{
	commandMsg(client, "INVITE");
	std::string	msg;
	// std::string	chn = inputs[2].erase(inputs[2].find_last_not_of(" \n\r\t")+1);
	// inputs[1] = strCleaner(inputs[2]);
	std::string	chn = strCleaner(inputs[2]);
	// inputs[1].erase(inputs[1].find_last_not_of(" \n\r\t")+1);
	inputs[1] = strCleaner(inputs[1]);
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
	msg = "User "+ client.nickName +" inviting "+ inputs[1] +" to channel "+ chn +"\n";

	execute(send(targetFd, msg.c_str(), msg.length(), 0), "Invite", 0);
}
