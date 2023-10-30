#include "../../include/Server.hpp"

// //	/INVITE hedef_kullanici #hedef_kanal
// //	:Sunucu_Adı INVITE Davet_Eden_Kullanıcı Davet_Edilen_Kullanıcı #Hedef_Kanal

void	Server::invite_command( Client &client )
{
	commandMsg(client, "INVITE");
	std::string	msg;
	// std::string	chn = inputs[2].erase(inputs[2].find_last_not_of(" \n\r\t")+1);
	std::string	chn = strCleaner(inputs[2]);
	inputs[1] = strCleaner(inputs[1]);
	// inputs[1] = strCleaner(inputs[2]);
	// inputs[1].erase(inputs[1].find_last_not_of(" \n\r\t")+1);
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
	msg = "User "+ client.nickName +" inviting "+ inputs[1] +" to channel "+ chn +"\r\n";
	execute(send(targetFd, msg.c_str(), msg.length(), 0), "Invite", 0);
}

// #include "../../inc/Server.hpp"

// //USER <kullanıcı adı> <gerçek ad> <sunucu adı> :<kullanıcı hakkında diğer ayrıntılar>

// void Server::user(Client &client){
// 	if (cmd.size() > 5){
// 		std::vector<std::string>::iterator it = cmd.begin();
// 		std::vector<std::string>::iterator it2;
// 		it2 = it;
// 		it++;

// 		while (it != cmd.end()){
// 			if (*it == "USER"){
// 				it++;
// 				it2++;
// 				client._user = *it;
// 			}
// 			else if ((*it)[0] == ':'){
// 				client._host = *it2;
// 				break;
// 			}
// 			else{
// 				it++;
// 				it2++;
// 			}
// 		}
// 		std::string msg = "Welcome to irc server that made by oozcan osarihan and ebattal!\n";
// 		send(client.fd, msg.c_str(), msg.length(), 0);
// 	}
// 	else {
// 		std::string msg = "ERROR! paramaters should be like this USER <kullanıcı adı> <gerçek ad> <sunucu adı> :<kullanıcı hakkında diğer ayrıntılar>\n";
// 		send(client.fd, msg.c_str(), msg.length(), 0);
// 		msg.clear();
// 	}
// }

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