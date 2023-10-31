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
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Invite", 0);
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
	msg = "You have been invited to channel " + chn + " you can type /join to join that channel\n";
	execute(send(targetFd, msg.c_str(), msg.length(), 0), "Invite", 0);
}

// #include "../../inc/Server.hpp"

// //USER <kullanıcı adı> <gerçek ad> <sunucu adı> :<kullanıcı hakkında diğer ayrıntılar>
// void	Server::invite_command( Client &client )
// {
//     std::cout << "INVITE FONKSIYONU\n";
//     int target = GetChannelFromName(inputs[2]);
//         if (target > -1)
// 		{
//             // if (!strncmp(Client.nickName.c_str(), channels[i]._admin.c_str(), channels[i]._admin.length())){
//             if (channels[target].isOperator(client.nickName))
// 			{
//                 channels[target].whiteList.push_back(inputs[1]);
//                 for (unsigned long int j = 0; j < clients.size(); j++){
//                     if (!strncmp(inputs[1].c_str(),clients[j].nickName.c_str(), inputs[1].length())){
//                         std::string msg = "You have been invited to channel " + inputs[2] + " you can type /join to join that channel\n";
//                         send(clients[j].fd, msg.c_str(), msg.length(), 0);
//                     }
//                 }
//             }
//         }
// }