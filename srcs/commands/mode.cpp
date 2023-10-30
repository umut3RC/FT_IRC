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
	else if (inputs[0] == "MODE" && channels[chnIndex].isOperator(client.nickName) &&
		!strncmp(channels[chnIndex].chnName.c_str(), inputs[1].c_str(), inputs[1].length()))//channels[chnIndex].chnName == inputs[1])
	{
		if (!strncmp(inputs[2].c_str(), "+k", strlen("+k")))
		{
			std::cout << "IRC: Channel's pass is changed.";
			channels[chnIndex].chnPass = inputs[3];
			channels[chnIndex].hasPass = true;
		}
		else if (!strncmp(inputs[2].c_str(), "+o", strlen("+o")))
		{
			std::cout << "IRC: New Operator added.";
			channels[chnIndex].chnOperators.push_back(inputs[3]);
		}
		else if (!strncmp(inputs[2].c_str(), "+n", strlen("+n")))
			channels[chnIndex].modeN = true;
		else if (!strncmp(inputs[2].c_str(), "+l", strlen("+l")))
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
		else if (!strncmp(inputs[2].c_str(), "+p", strlen("+p")))
		{
			channels[chnIndex].modeP = true;
		}
	}
}
