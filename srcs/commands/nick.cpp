#include "../../include/Server.hpp"

//----------------------------
void	Server::nick_command( Client &client )
{
	std::string msg;
	int	targetFd = GetClientFdFromName(inputs[1], client.fd);
	int nindex = 0;
	if (targetFd > 0)
	{
		std::cout << "IRC: Nick is already used!\n";
		quit_command(client);
	}
	// printInputs();
	if ((int)inputs.size() > 3)//ilk bağlantıda nick farklı
	{
		unsigned long int i = 0;
		while (i < inputs.size())
		{
			if (inputs[i] == "NICK")
			{
				nindex = i + 1;
				client.nickName = inputs[i + 1];
			}
			if (inputs[i] == "USER")
				client.userName = inputs[i + 1];
			else if (inputs[i][0] == ':')
				client.host = inputs[i - 1];
			i++;
		}
	}
	else
	{
		msg = getprefix(client);
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Nick", 0);
		for (unsigned long int k = 0; k < channels.size(); k++)
		{
			if (channels[k].isOperator(client.nickName))
			{
				if (channels[k].isOperator(client.nickName))
				{
					for (int j = 0; j < (int)channels[k].chnOperators.size(); j++)
					{
						if (channels[k].chnOperators[j] == client.nickName)
						{
							channels[k].chnOperators[j] = inputs[1];
							break;
						}
					}
				}
			}
		}
		client.nickName = inputs[1];
	}
}
//----------------------------

// /*working*/
// void	Server::nick_command( Client &client )
// {
// 	std::string msg;
// 	int	targetFD;
// 	printInputs();
// 	if (inputs.empty() || inputs[0].empty() || inputs[1].empty())
// 	{
// 		msg = "ERROR :User with alias" + inputs[1] + "not found\r\n";
// 		execute(send(client.fd, msg.c_str(), sizeof(msg.c_str()), 0), "ERR\n");
// 		return;
// 	}
// 	targetFD = GetClientFdFromName(inputs[1], client.fd);
// 	if (targetFD > 0)
// 	{
// 		msg = "ERROR :Nick name is previously used\r\n";
// 		execute(send(client.fd, msg.c_str(), sizeof(msg.c_str()), 0), "ERR\n");
// 		return ;
// 	}
	
// 	for (int j = 0; j < (int)channels.size(); j++)
// 	{
// 		if (channels[j].isOperator(client.nickName))
// 		{
// 			if (channels[j].isOperator(client.nickName))
// 			{
// 				for (int k = 0; k < (int)channels[j].chnOperators.size(); k++)
// 				{
// 					if (channels[j].chnOperators[k] == client.nickName)
// 					{
// 						channels[j].chnOperators[k] = inputs[1];
// 						break;
// 					}
// 				}
// 			}
// 		}
// 	}
// 	client.nickName = inputs[1];
// 	msg = ":" + getprefix(client) + " NICK " + inputs[1] + "\r\n";
// 		execute(send(client.fd, msg.c_str(), sizeof(msg.c_str()), 0), "ERR\n");
// }

// void	Server::nick_command( Client &client )
// {
// 	std::string msg;
// 	std::cout << "NICK FUNC" << '\n';
// 	int nindex = 0;
// 	if (client.passchk == false){
// 		std::cout << "ft_ex" << '\n';
// 		msg = "ERROR! passcheck failed!\n";
// 		send(client.fd, msg.c_str(), strlen(msg.c_str()), 0);
// 		msg.clear();
// 		quit_command(client);
// 	}
// 	if (serverClntNum == 1 && client.passchk == false)
// 		return;
// 	if (!client.isFirstNickAssigment)
// 	{
// 		unsigned long int i = 0;
// 		while (i < inputs.size())
// 		{
// 			if (inputs[i] == "NICK"){
// 				nindex = i + 1;
// 				//ilk defa nick alan icin ayni nick kontrolu
// 				for (unsigned long int j = 0; j < clients.size(); j++){
// 					if (inputs[nindex] == clients[j].nickName){
// 						std::cout << "nick in use" << '\n';
// 							quit_command(client);
// 					}
// 				}
// 				client.nickName = inputs[i + 1];
// 			}
// 			if (inputs[i] == "USER")
// 				client.userName = inputs[i + 1];
// 			else if (inputs[i][0] == ':')
// 				client.host = inputs[i - 1];
// 			i++;
// 		}
// 		//ikinci nick komutunda yeniden buraya gelmesin diye
// 		client.isFirstNickAssigment = true;
// 	}
// 	else
// 	{
// 		//ayni nick kontrolu
// 		for (unsigned long int i = 0; i < clients.size(); i++){
// 			std::cout << "SPINN" << '\n';
// 			if (!strncmp(inputs[1].c_str(), clients[i].nickName.c_str(), strlen(inputs[1].c_str()))){
// 				std::cout << "nick in use" << '\n';
// 				msg = "ERROR! nick in use!\n";
// 				send(client.fd, msg.c_str(), msg.length(), 0);
// 				msg.clear();
// 				if (!client.nickName.empty())
// 					return;
// 				else
// 					quit_command(client);
// 			}
// 		}
// 		// var olan kisinin nickinin degistigi kisim
// 		std::cout << "nickfunc." << client.nickName << '\n';
// 		std::string newnick = ':' + client.nickName;
// 		newnick = getprefix(client);
// 		newnick += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 		send(client.fd, newnick.c_str(), newnick.length(), 0);
// 		// for (unsigned long int k = 0; k < channels.size(); k++)
// 		// {
// 		// 	if (client.nickName == channels[k]._admin)
// 		// 	{
// 		// 		std::cout << "ADMIN degisti" << '\n';
// 		// 		channels[k]._admin = inputs[1];
// 		// 	}
// 		// }
// 		client.nickName = inputs[1];
// 	}
// }
