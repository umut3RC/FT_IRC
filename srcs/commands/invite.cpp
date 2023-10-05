#include "../../include/Server.hpp"

//	/INVITE hedef_kullanici #hedef_kanal
//	:Sunucu_Adı INVITE Davet_Eden_Kullanıcı Davet_Edilen_Kullanıcı #Hedef_Kanal

void	Server::invite_command( Client &client )
{
	commandMsg(client, "INVITE");
	std::string	msg;
	std::string	chn = inputs[2];
	int	targetFd;
	int	targetChn;
	msg = ":" + getprefix(client) + " INVITE " + client.nickName + " " + inputs[1] + " " + chn;
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

	execute(send(targetFd, msg.c_str(), msg.length(), 0), "ERR\n");
}
//-OLD-VVV-----------------------------
// void	Server::invite_command( Client &client )
// {
// 	commandMsg(client, "INVITE");
// 	std::string msg;
// 	int targetFd;
// 	msg = ":" + getprefix(client) + " INVITE " + client.nickName + " " + inputs[1] + " " + inputs[2];
// 	targetFd = GetClientFdFromName(inputs[1], client.fd);
// 	if (targetFd < 0)
// 	{
// 		std::cout << "IRC: Client is not founded" << std::endl;
// 		return;
// 	}
// 	execute(send(targetFd, msg.c_str(), sizeof(msg.c_str()), 0), "ERR\n");
// }
//-OLD-^^^----------------------------------------
// #include "../../inc/Server.hpp"

// void Server::invite(Client &Client){
    // std::cout << "INVITE FONKSIYONU\n";
    // for (unsigned long int i = 0; i < channels.size(); i++){
        // if (!strncmp(cmd[2].c_str(), channels[i]._chname.c_str(), cmd[2].length())){
            // if (!strncmp(Client._nick.c_str(), channels[i]._admin.c_str(), channels[i]._admin.length())){
                // channels[i]._whitelist.push_back(cmd[1]);
                // for (unsigned long int j = 0; j < clients.size(); j++){
                    // if (!strncmp(cmd[1].c_str(),clients[j]._nick.c_str(), cmd[1].length())){
                        // std::string msg = "You have been invited to channel " + cmd[2] + " you can type /join to join that channel\n";
                        // send(clients[j].fd, msg.c_str(), msg.length(), 0);
                    // }
                // }
            // }
        // }
    // }
// }