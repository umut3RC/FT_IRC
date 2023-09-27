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
		if (!strncmp(clients[i]._nickName.c_str(), targetName.c_str(), strlen(targetName.c_str())) && clients[i].fd != fd)
		{
			std::cout << "finded\n";
			return(clients[i].fd);
		}
	}
	std::cout << "IRC: No user for PRIVMSG\n";
	return (-1);
}
bool	Server::GetChannelFromName(std::string targetName)
{
	// for (int i = 0; i < (int)channels.size(); i++)
	// {
	// 	if (!channels[i]._nickName.compare(targetName))
	// 	{ 
	// 		return(true);
	// 	}
	// }
	(void)targetName;
	return (false);
}

// void Server::privmsg_command(Client &client)
// {
// 	std::cout << "IRC: PRIVMSG command\n";
// 	(void)client;
// 	int	targetFd;

// 	targetFd = GetClientFdFromName(inputs[1], client.fd);
// 	std::string dest = inputs[1];
// 	std::string msg = getprefix(client);
// 	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
// 	for (unsigned long int l = 2; l < inputs.size(); l++){
// 		msg = msg + inputs[l];
// 		msg = msg + ' ';
// 	}
// 	msg += '\n';
// 	std::cout << msg  << " *-* " << targetFd << '\n';
// 	if (targetFd < 0)
// 	{
// 		// if(!GetClientFdFromName(inputs[1]))
// 		// {
// 			// std::cout << "IRC: User(" << inputs[1] << ") is not finded\r\n";
// 			// msg = "User is not finded!\n";
// 			// execute(send(targetFd, msg.c_str(), sizeof(msg), 0), "Err\n");
// 		// }
// 		std::cout << "-1\n";
// 		throw std::runtime_error("-_-\n");
// 	}
// 	execute(send(targetFd, msg.c_str(), sizeof(msg), 0), "Err\n");
// }







//----------------------------------------------
void Server::privmsg_command(Client &client)
{
	std::cout << "PRIVMSG FONKSIYONU" << '\n';
	std::string dest = inputs[1];
	std::string msg = getprefix(client);
	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
	for (unsigned long int l = 2; l < inputs.size(); l++){
		msg = msg + inputs[l];
		msg = msg + ' ';
	}
	msg += '\n';
	std::cout << msg << '\n';
	bool inch = 0;
	if (inputs[1][0] == '#'){
		for (unsigned long int j = 0; j < channels.size(); j++){
			std::string temp = channels[j]._chname;
			if (!strncmp(dest.c_str(), temp.c_str(), strlen(dest.c_str()))){
				if (channels[j].ifn){
					for(unsigned long int l = 0; l < channels[j].chnclients.size(); l++){
						if (channels[j].chnclients[l]._nickName == client._nickName)
							inch = 1;
					}
					if (inch){
						for (int k = 0; k < channels[j]._clientnum; k++){
							if (channels[j].chnclients[k]._nickName != client._nickName)
								send(channels[j].chnclients[k].fd, msg.c_str(), msg.length(), 0);
						}
					}
					else{
						std::cout << "CLIENT NOT IN THE SERVER CLIENT LIST !!!!!!" << '\n';
						msg.clear();
						msg = "ERROR! You're not on that channel\n";
						send(client.fd, msg.c_str(), msg.length(), 0);
						msg.clear();
					}
					return;
				}
				else{
					for (int k = 0; k < channels[j]._clientnum; k++){
						if (channels[j].chnclients[k]._nickName != client._nickName)
							send(channels[j].chnclients[k].fd, msg.c_str(), msg.length(), 0);
					}
				}
			}
		}
	}
	else{
		for (unsigned long int k = 0; k < clients.size() ; k++){
			std::cout << msg << '\n';
			if (!strncmp(dest.c_str(), (clients[k]._nickName).c_str(), strlen(dest.c_str()))){
				send(clients[k].fd , msg.c_str(), msg.length(), 0);
				return;
			}
		}
		return;
	}
}
