#include "../../include/Server.hpp"

void	Server::mode_command( Client &client )
{
	commandMsg(client, "MODE");
	int	chnIndex = GetChannelFromName(inputs[1]);
	std::string msg;
	if (chnIndex < 0)
	{
		msg = "You need join a channel";
		std::cout << msg << "\n";
	}
	else if (inputs[0] == "MODE" && channels[chnIndex].isOperator(client.nickName) && channels[chnIndex].chnName == inputs[1])
		// !strncmp(channels[chnIndex].chnName.c_str(), inputs[1].c_str(), inputs[1].length()))
	{
		if (inputs[2] == "+k")
		{
			std::cout << "IRC: Channel's pass is changed.";
			// if ((int)inputs.size() < 3)
			// 	throw std::runtime_error("ERR");
			channels[chnIndex].chnPass = inputs[3];
			channels[chnIndex].hasPass = true;
		}
		else if (inputs[2] == "+o")
		{
			std::cout << "IRC: New Operator added.";
			channels[chnIndex].chnOperators.push_back(inputs[3]);
		}
		else if (inputs[2] == "+n")
			channels[chnIndex].modeN = true;
		else if (inputs[2] == "+l")
		{
			if (channels[chnIndex].chnClientsNum > std::atoi(inputs[3].c_str()))
			{
				std::string msg = "ERROR! MAX USER CANNOT BE LOWER THAN EXIST USER COUNT\r\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Mode", 0);
				return;
			}
			else{
				channels[chnIndex].maxUser = std::atoi(inputs[3].c_str());
				return;
			}
		}
		else if (inputs[2] == "+p")
		{
			channels[chnIndex].modeP = true;
		}
	}
	// else
	// {
	// 	msg = ERR_CHANOPRIVSNEEDED(getprefix(client), channels[chnIndex].chnName);

	// 	execute(send(client.fd, msg.c_str(), sizeof(msg.c_str()), 0), "ERR");
	// 	return ;
	// }
}

//-------------------------------------------------------
// void	Server::mode_command( Client &client )
// {
// 	std::cout << "MODE FONKSIYONU\n";
// 	int cindex = 0;
// 	for (unsigned long int i=0; i < channels.size(); i++){
// 		if (!strncmp(channels[i].chnName.c_str(), inputs[1].c_str(), inputs[1].length()))
// 			cindex = i;
// 	}
// 	if (inputs[0] == "MODE"){
// 		if (channels[cindex].isOperator(client.nickName))
// 		{
// 			if (inputs[2] == "+k"){
// 				if (!strncmp(channels[cindex].chnName.c_str(), inputs[1].c_str(), inputs[1].length())){
// 					channels[cindex].chnPass = inputs[3];
// 					channels[cindex].hasPass = 1;
// 				}
// 			}
// 			else if (inputs[2] == "+l"){
// 				if (!strncmp(channels[cindex].chnName.c_str(), inputs[1].c_str(), inputs[1].length())){
// 					int tempmax = std::atoi(inputs[3].c_str());
// 					if (channels[cindex].chnClientsNum > tempmax){
// 						std::string msg = "ERROR! MAX USER CANNOT BE LOWER THAN EXIST USER COUNT\n";
// 						send(client.fd, msg.c_str(), msg.length(), 0);
// 						return;
// 					}
// 					else{
// 						channels[cindex].maxUser = tempmax;
// 						return;
// 					}
// 				}
// 				return;
// 			}
// 			else if (!strncmp(inputs[2].c_str(), "+n", strlen("+n"))){
// 				if (!strncmp(channels[cindex].chnName.c_str(), inputs[1].c_str(), inputs[1].length())){
// 						channels[cindex].modeN = 1;
// 				}
// 			}
// 			else if (!strncmp(inputs[2].c_str(), "+p", strlen("+p"))){
// 				if (!strncmp(channels[cindex].chnName.c_str(), inputs[1].c_str(), inputs[1].length())){
// 					channels[cindex].modeP = 1;
// 				}
// 			}
// 		}
// 	}
// }
