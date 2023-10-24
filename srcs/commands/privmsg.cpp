#include "../../include/Server.hpp"

/*
target user
message
message
message
...
*/
//--RPL_PRIVMSG----------------------------------------------------------------VLASTA-LASTA-FİNİTOSHİBAV
void Server::privmsg_command(Client &client)
{
	commandMsg(client, "PRIVMSG");
	std::string	msg = getprefix(client);
	std::string	targetName = inputs[1];
	int	targetFd = GetClientFdFromName(inputs[1], client.fd);
	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
	for (unsigned long int i = 2; i < inputs.size(); i++)
	{
		msg = msg + inputs[i];
		msg = msg + ' ';
	}
	msg += "\r\n";
	if (inputs[1][0] == '#')
	{
		targetFd = GetChannelFromName(targetName);
		if (targetFd < 0)
		{
			return;
		}
		if (channels[targetFd].modeN)
		{
			for(unsigned long int l = 0; l < channels[targetFd].chnClients.size(); l++)
			{
				if (channels[targetFd].chnClients[l].nickName == client.nickName)
				{
					for (int k = 0; k < channels[targetFd].chnClientsNum; k++)
					{
						if (channels[targetFd].chnClients[k].nickName != client.nickName)
							execute(send(channels[targetFd].chnClients[k].fd, msg.c_str(), msg.length(), 0), "Privmsg", 0);
					}
				}
			}
			msg = msg +  " " + ERR_NOTONCHANNEL(client.nickName, inputs[1]) + "\r\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Privmsg", 0);
			return ;
		}
		else if (targetFd > -1)
		{
			std::cout << "IRC: Sended to clients on "<< inputs[1] <<" channel.\n";
			for (int k = 0; k < channels[targetFd].chnClientsNum; k++)
			{
				if (channels[targetFd].chnClients[k].nickName != client.nickName)
					execute(send(channels[targetFd].chnClients[k].fd, msg.c_str(), msg.length(), 0), "Privmsg", 0);
			}
		}
	}
	else
	{
		if (targetFd > -1)
		{
			// execute(send(targetFd, msg.c_str(), msg.length(), 0), "Err\n");
			execute(send(targetFd, msg.c_str(), msg.length(), 0), "Privmsg", 0);
		}
	}
}
//---------------------------------------------------------------------------------------^^^^^^^
//----------------------------------------------
// void Server::privmsg_command(Client &client)
// {
// 	std::string dest = inputs[1];
// 	std::string msg = getprefix(client);
// 	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
// 	for (unsigned long int l = 2; l < inputs.size(); l++){
// 		msg = msg + inputs[l];
// 		msg = msg + ' ';
// 	}
// 	msg += '\n';
// 	std::cout << msg << '\n';
// 	// if (inputs[1][0] == '#'){
// 	// 	for (unsigned long int j = 0; j < channels.size(); j++){
// 	// 		std::string temp = channels[j].chnName;
// 	// 		if (!strncmp(dest.c_str(), temp.c_str(), strlen(dest.c_str()))){
// 	// 			if (channels[j].modeN){
// 	// 				for(unsigned long int l = 0; l < channels[j].chnClients.size(); l++){
// 	// 					if (channels[j].chnClients[l].nickName == client.nickName)
// 	// 						inch = 1;
// 	// 				}
// 	// 				if (inch){
// 	// 					for (int k = 0; k < channels[j].chnClientsNum; k++){
// 	// 						if (channels[j].chnClients[k].nickName != client.nickName)
// 	// 							send(channels[j].chnClients[k].fd, msg.c_str(), msg.length(), 0);
// 	// 					}
// 	// 				}
// 	// 				else{
// 	// 					std::cout << "CLIENT NOT IN THE SERVER CLIENT LIST !!!!!!" << '\n';
// 	// 					msg.clear();
// 	// 					msg = "ERROR! You're not on that channel\n";
// 	// 					send(client.fd, msg.c_str(), msg.length(), 0);
// 	// 					msg.clear();
// 	// 				}
// 	// 				return;
// 	// 			}
// 	// 			else{
// 	// 				for (int k = 0; k < channels[j].chnClientsNum; k++){
// 	// 					if (channels[j].chnClients[k].nickName != client.nickName)
// 	// 						send(channels[j].chnClients[k].fd, msg.c_str(), msg.length(), 0);
// 	// 				}
// 	// 			}
// 	// 		}
// 	// 	}
// 	// }
// 	// else{
// 		for (unsigned long int k = 0; k < clients.size() ; k++){
// 			std::cout << msg << '\n';
// 			if (!strncmp(dest.c_str(), (clients[k].nickName).c_str(), strlen(dest.c_str()))){
// 				send(clients[k].fd , msg.c_str(), msg.length(), 0);
// 				return;
// 			}
// 		}
// 		return;
// 	// }
// }


// void Server::privmsg_command(Client &client)
// {
// 	commandMsg(client, "PRIVMSG");
// 	std::string	msg;// = getprefix(client);
// 	std::string	targetName = inputs[1];
// 	int	targetFd = GetClientFdFromName(inputs[1], client.fd);
// 	// msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
// 	for (unsigned long int i = 2; i < inputs.size(); i++)
// 	{
// 		msg = msg + inputs[i];
// 		msg = msg + ' ';
// 	}
// 	msg += "\r\n";
// 	if (inputs[1][0] == '#')
// 	{
// 		targetFd = GetChannelFromName(targetName);
// 		std::string temp = channels[targetFd].chnName;
// 		if (channels[targetFd].modeN)
// 		{
// 			for(unsigned long int l = 0; l < channels[targetFd].chnClients.size(); l++)
// 			{
// 				if (channels[targetFd].chnClients[l].nickName == client.nickName)
// 				{
// 					for (int k = 0; k < channels[targetFd].chnClientsNum; k++)
// 				{
// 					if (channels[targetFd].chnClients[k].nickName != client.nickName)
// 						send(channels[targetFd].chnClients[k].fd, msg.c_str(), msg.length(), 0);
// 				}
// 				}
// 			}
// 			msg = RPL_PRIVMSG(getprefix(client), client.nickName, msg);
// 			execute(send(client.fd, msg.c_str(), msg.length(), 0), "ERR");
// 			return ;
// 		}
// 		else
// 		{
// 			for (int k = 0; k < channels[targetFd].chnClientsNum; k++)
// 			{
// 				if (channels[targetFd].chnClients[k].nickName != client.nickName)
// 				{
// 					msg = RPL_PRIVMSG(getprefix(client), targetName, msg);
// 					send(channels[targetFd].chnClients[k].fd, msg.c_str(), msg.length(), 0);
// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if (targetFd < 0)
// 		{
// 			targetFd = GetChannelFromName(inputs[1]);
// 			if(targetFd < 0)
// 			{
// 				std::cout << "-1\n";
// 				execute(send(client.fd, msg.c_str(), sizeof(msg), 0), "Err\n");
// 			}
// 			execute(send(targetFd, msg.c_str(), msg.length(), 0), "Err\n");
// 		}
// 		msg = RPL_PRIVMSG(getprefix(client), client.nickName, msg);
// 		execute(send(targetFd, msg.c_str(), msg.length(), 0), "Err\n");
// 	}
// 	return;
// }








// void Server::privmsg_command(Client &client)
// {
// 	std::cout << "PRIVMSG FONKSIYONU" << '\n';
// 	std::string dest = inputs[1];
// 	std::string msg = getprefix(client);
// 	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
// 	for (unsigned long int l = 2; l < inputs.size(); l++){
// 		msg = msg + inputs[l];
// 		msg = msg + ' ';
// 	}
// 	msg += '\n';
// 	int inch = 0;
// 	std::cout << msg << '\n';
// 	if (inputs[1][0] == '#'){
// 		for (unsigned long int j = 0; j < channels.size(); j++){
// 			std::string temp = channels[j].chnName;
// 			if (!strncmp(dest.c_str(), temp.c_str(), strlen(dest.c_str()))){
// 				if (channels[j].modeN){
// 					for(unsigned long int l = 0; l < channels[j].chnClients.size(); l++){
// 						if (channels[j].chnClients[l].nickName == client.nickName)
// 							inch = 1;
// 					}
// 					if (inch){
// 						for (int k = 0; k < channels[j].chnClientsNum; k++){
// 							if (channels[j].chnClients[k].nickName != client.nickName)
// 								send(channels[j].chnClients[k].fd, msg.c_str(), msg.length(), 0);
// 						}
// 					}
// 					else{
// 						std::cout << "CLIENT NOT IN THE SERVER CLIENT LIST !!!!!!" << '\n';
// 						msg.clear();
// 						msg = "ERROR! You're not on that channel\n";
// 						send(client.fd, msg.c_str(), msg.length(), 0);
// 						msg.clear();
// 					}
// 					return;
// 				}
// 				else{
// 					for (int k = 0; k < channels[j].chnClientsNum; k++){
// 						if (channels[j].chnClients[k].nickName != client.nickName)
// 							send(channels[j].chnClients[k].fd, msg.c_str(), msg.length(), 0);
// 					}
// 				}
// 			}
// 		}
// 	}
// 	else{
// 		for (unsigned long int k = 0; k < clients.size() ; k++){
// 			std::cout << msg << '\n';
// 			if (!strncmp(dest.c_str(), (clients[k].nickName).c_str(), strlen(dest.c_str()))){
// 				send(clients[k].fd , msg.c_str(), msg.length(), 0);
// 				return;
// 			}
// 		}
// 		return;
// 	}
// }
