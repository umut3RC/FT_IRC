#include "../../include/Server.hpp"

//JOIN #Oda_adi PASS

int	Server::findChannel( void )
{
	int	index = -1;
	if (inputs.size() < 2)
		return(index);
	for (int i = 0 ; i < (int)channels.size(); i++)
	{
		if (inputs[1] == channels[i].chnName)
		{
			index = i;
			return (index);
		}
	}
	return (index);
}
void	Server::createNewChannel(Client &client)
{
	std::string msg = getprefix(client);
	Channel newChannel(inputs[1]);
	if (inputs.size() == 2)
		newChannel.chnPass = inputs[2];
	newChannel.chnClients.push_back(client);
	newChannel.chnClientsNum++;
	newChannel.chnOperators.push_back(client.nickName);
	newChannel.hasPass = false;
	newChannel.modeN = true;
	newChannel.modeI = false;
	channels.push_back(newChannel);
	serverChnNum++;
	msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
	execute(send(client.fd, msg.c_str(), msg.length(), 0), "Create New Channel", 1);
	msg.clear();
	std::cout << "IRC: New Channel created.\n";
}

void	Server::join_command( Client &client )
{
	commandMsg(client, "JOIN");
	int	index;
	std::string msg = getprefix(client);
	index = findChannel();
	if (inputs[1][0] != '#')
		inputs[1] = '#' + inputs[1];
	// inputs[1].erase(inputs[1].find_last_not_of(" \n\r\t")+1);
	inputs[1] = strCleaner(inputs[1]);
	if (index > -1)
	{
		if (channels[index].hasPass)
		{
			if (inputs.size() < 3)
			{
				msg = ERR_NEEDMOREPARAMS(getprefix(client), "Join");
				msg += "\r\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
			}
			if (strncmp(inputs[2].c_str(), channels[index].chnPass.c_str(), channels[index].chnPass.length()))
			{
				std::cout << "IRC: Channel has pass\n"; 
				msg = ERR_PASSWDMISMATCH(client.nickName);
				msg += "\r\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
				msg.clear();
				return;
			}
		}
		if (channels[index].maxUser == channels[index].chnClientsNum)
		{
			msg = ERR_CHANNELISFULL(getprefix(client), inputs[1]);
			msg += "\r\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
			return;
		}
		if (channels[index].modeI == true)
		{
			if (channels[index].whiteList.empty())
			{
				std::cout << "IRC: White List is empty!\n";
				msg = ERR_INVITEONLYCHAN(inputs[1]);
				msg += "\r\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
				return;
			}
			for (unsigned long int l = 0; l < channels[index].whiteList.size(); l++)
			{
				// if (!strncmp(channels[index].whiteList[l].c_str(), client.nickName.c_str(), channels[index].whiteList[l].length()))
				if (channels[index].whiteList[l] == client.nickName)
				{
					channels[index].chnClients.push_back(client);
					channels[index].chnClientsNum++;
					msg = msg + ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
					for (int j = 0; j < channels[index].chnClientsNum; j++)
					{
						execute(send(channels[index].chnClients[j].fd, msg.c_str(), msg.length(), 0), "Join", 0);
					}
					// std::vector<std::string>::iterator	wit = channels[channels.size() - 1].whiteList.begin();
					// while (wit != channels[channels.size() - 1].whiteList.end())
					// {
					// 	std::cout << "WT: >>" << *wit << "<<\n";
					// 	wit++;
					// }
					// msg.clear();
					return;
				}
			}
			std::cout << "IRC: You are not invited!\n";
			msg = ERR_INVITEONLYCHAN(inputs[1]);
			msg += "\r\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
			return;
		}
		channels[index].chnClients.push_back(client);
		channels[index].chnClientsNum++;
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		for (int j = 0; j < channels[index].chnClientsNum; j++)
		{
			execute(send(channels[index].chnClients[j].fd, msg.c_str(), msg.length(), 0), "Join", 0);
		}
		return;
	}
	else
		createNewChannel(client);
}


/*WORKING*/
// void	Server::join_command( Client &client )
// {	std::cout << "JOIN FONKSIYONU" << '\n';
// 	std::string chn = getprefix(client);
// 	if (inputs.size() > 3){
// 		std::cerr << "join ARG Error!" << std::endl;
// 		chn = "join args must be like this /join <channel> <channel passwd>\n";
// 		send(client.fd, chn.c_str(), chn.length(), 0);
// 		chn.clear();
// 		return;
// 	}
// 	printInputs();
// 	if (inputs[1][0] != '#')
// 		inputs[1] = '#' + inputs[1];
// 	for (unsigned long int i = 0; i < channels.size(); i++)
// 	{
// 		if (!strncmp(inputs[1].c_str(), channels[i].chnName.c_str(), inputs[1].length()))
// 		{
// 			if (channels[i].hasPass == 1){
// 				if (strncmp(inputs[2].c_str(), channels[i].chnPass.c_str(), channels[i].chnPass.length())){
// 					std::cout << "join if pass check!1\n"; 
// 					chn = "ERROR! PLEASE JOIN WITH CHANNEL PASSWORD!\n";
// 					send(client.fd, chn.c_str(), chn.length(), 0);
// 					chn.clear();
// 					return;
// 				}
// 			}
// 			if (channels[i].maxUser == channels[i].chnClientsNum){
// 				chn = "ERROR! YOU CANNOT JOIN THIS CHANNEL USER LIMIT REACHED\n";
// 				send(client.fd, chn.c_str(), chn.length(), 0);
// 				chn.clear();
// 				return;
// 			}
// 			if (channels[i].modeI == 1){
// 				std::vector<std::string>::iterator	wit = channels[0].whiteList.begin();
// 				while (wit != channels[0].whiteList.end())
// 				{
// 					std::cout << "WT: >>" << *wit << "<<\n";
// 					wit++;
// 				}
// 				std::cout << "ifp == 1\n";
// 				if (channels[i].whiteList.empty())
// 				{
// 					chn = "ERROR! White list is empty!\n";
// 					send(client.fd, chn.c_str(), chn.length(), 0);
// 					return;
// 				}
// 				for (unsigned long int l = 0; l < channels[i].whiteList.size(); l++){
// 					if (!strncmp(channels[i].whiteList[l].c_str(), client.nickName.c_str(), channels[i].whiteList[l].length()) && !channels[i].whiteList.empty()){
// 						channels[i].chnClients.push_back(client);
// 						channels[i].chnClientsNum++;
// 						chn += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 						for (int j = 0; j < channels[i].chnClientsNum; j++){
// 							send(channels[i].chnClients[j].fd, chn.c_str(), chn.length(), 0);
// 						}
// 						chn.clear();
// 						return;
// 					}
// 					else{
// 						chn = "ERROR! You are not invited!\n";
// 						send(client.fd, chn.c_str(), chn.length(), 0);
// 						return;
// 					}
// 				}
// 			}
// 			channels[i].chnClients.push_back(client);
// 			channels[i].chnClientsNum++;
// 			std::cout << "CLNUM:" << channels[i].chnClientsNum << std::endl;
// 			chn += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 			for (int j = 0; j < channels[i].chnClientsNum; j++){
// 				send(channels[i].chnClients[j].fd, chn.c_str(), chn.length(), 0);
// 			}
// 			return;
// 		}
// 	}
// 	Channel newch(inputs[1]);
// 	if (inputs.size() == 2)
// 		newch.chnOperators.push_back(inputs[2]);
// 	newch.chnClients.push_back(client);
// 	newch.chnClientsNum++;
// 	newch.chnOperators.push_back(client.nickName);
// 	channels.push_back(newch);
// 	serverChnNum++;
// 	chn += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 	std::cout << "SENDIN USTU" << '\n';
// 	send(client.fd, chn.c_str(), chn.length(), 0);
// 	chn.clear();
// }
