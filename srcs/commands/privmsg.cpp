#include "../../include/Server.hpp"

/*
target user
message
message
message
...
*/

int	Server::GetClientFdFromName(std::string targetName, int fd)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
		if (!strncmp(clients[i].nickName.c_str(), targetName.c_str(), strlen(targetName.c_str())) && clients[i].fd != fd)
		{
			std::cout << "IRC: Client is finded.\n";
			return(clients[i].fd);
		}
	}
	std::cout << "IRC: No client in this name.\n";
	return (-1);
}
int	Server::GetChannelFromName(std::string targetName)
{
	for (int i = 0; i < (int)channels.size(); i++)
	{
		if (!strncmp(channels[i].chnName.c_str(), targetName.c_str(), strlen(targetName.c_str())))
		{ 
			std::cout << "IRC: Channel is finded.\n";
			return(i);
		}
	}
	return (-1);
}

void Server::privmsg_command(Client &client)
{
	commandMsg(client, "PRIVMSG");
	std::string	msg = getprefix(client);
	std::string	targetName = inputs[1];
	int	targetFd = GetClientFdFromName(inputs[1], client.fd);
	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
	for (unsigned long int l = 2; l < inputs.size(); l++)
	{
		msg = msg + inputs[l];
		msg = msg + ' ';
	}
	msg += '\n';
	if (inputs[1][0] == '#')
	{
		targetFd = GetChannelFromName(targetName);
		std::string temp = channels[targetFd].chnName;
		if (channels[targetFd].modeN)
		{
			for(unsigned long int l = 0; l < channels[targetFd].chnClients.size(); l++)
			{
				if (channels[targetFd].chnClients[l].nickName == client.nickName)
				{
					for (int k = 0; k < channels[targetFd].chnClientsNum; k++)
				{
					if (channels[targetFd].chnClients[k].nickName != client.nickName)
						send(channels[targetFd].chnClients[k].fd, msg.c_str(), msg.length(), 0);
				}
				}
			}
			msg = "ERROR! You're not on that channel\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), "ERR");
			return ;
		}
		else
		{
			for (int k = 0; k < channels[targetFd].chnClientsNum; k++)
			{
				if (channels[targetFd].chnClients[k].nickName != client.nickName)
					send(channels[targetFd].chnClients[k].fd, msg.c_str(), msg.length(), 0);
			}
		}
	}
	else
	{
		if (targetFd < 0)
		{
			targetFd = GetChannelFromName(inputs[1]);
			if(targetFd < 0)
			{
				std::cout << "-1\n";
				execute(send(client.fd, msg.c_str(), sizeof(msg), 0), "Err\n");
			}
			execute(send(targetFd, msg.c_str(), msg.length(), 0), "Err\n");
		}
		execute(send(targetFd, msg.c_str(), msg.length(), 0), "Err\n");
	}
	return;
}

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
