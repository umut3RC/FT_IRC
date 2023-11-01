#include "../../include/Server.hpp"

void	Server::mode_command( Client &client )
{
	commandMsg(client, "MODE");
	int	chnIndex = GetChannelFromName(strCleaner(inputs[1]));
	std::string msg;
	if (chnIndex < 0)
	{
		msg = "You need join a channel";
		std::cout << msg << "\n";
	}
	else if (inputs[0] == "MODE" && channels[chnIndex].isOperator(client.nickName) &&
		!strncmp(channels[chnIndex].chnName.c_str(), inputs[1].c_str(), inputs[1].length()))
	{
		if (!strncmp(inputs[2].c_str(), "+k", strlen("+k")))
		{
			std::cout << "IRC: Channel's pass is changed.\n";
			channels[chnIndex].chnPass = inputs[3];
			channels[chnIndex].hasPass = true;
		}
		else if (!strncmp(inputs[2].c_str(), "-k", strlen("-k")))
		{
			std::cout << "IRC: Channel's pass is closed.\n";
			channels[chnIndex].hasPass = false;
		}
		else if (!strncmp(inputs[2].c_str(), "+o", strlen("+o")))
		{
			std::cout << "IRC: New Operator added.\n";
			channels[chnIndex].chnOperators.push_back(inputs[3]);
		}
		else if (!strncmp(inputs[2].c_str(), "+n", strlen("+n")))
		{
			std::cout << "IRC: +n activited for channel.\n";
			channels[chnIndex].modeN = true;
		}
		else if (!strncmp(inputs[2].c_str(), "-n", strlen("-n")))
		{
			std::cout << "IRC: -n de-activited for channel.\n";
			channels[chnIndex].modeN = false;
		}
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
		else if (!strncmp(inputs[2].c_str(), "+i", strlen("+i")))
		{
			std::cout << "IRC: +i activited for channel.\n";
			channels[chnIndex].modeI = true;
		}
		else if (!strncmp(inputs[2].c_str(), "-i", strlen("-i")))
		{
			std::cout << "IRC: -i de-activited for channel.\n";
			channels[chnIndex].modeI = false;
		}
	}
	else if (!channels[chnIndex].isOperator(client.nickName) && inputs.size() > 2)
	{
		msg = ERR_CHANOPRIVSNEEDED(client.nickName, inputs[1]);
		msg += "\r\n";
		std::cout << msg << '\n';
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Mode", 0);
	}
}
