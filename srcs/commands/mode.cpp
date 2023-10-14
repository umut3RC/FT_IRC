#include "../../include/Server.hpp"

void	Server::mode_command( Client &client )
{
	commandMsg(client, "MODE");
	// printInputs();
	int	chnIndex = GetChannelFromName(inputs[1]);
	std::string msg;
	if (chnIndex < 0)
	{
		msg = "You need join a channel";
		std::cout << msg << "\n";
	}
	else if (channels[chnIndex].isOperator(client.nickName))
	{
		if (inputs[2] == "+k")
		{
			if ((int)inputs.size() < 3)
				throw std::runtime_error("ERR");
			channels[chnIndex].chnPass = inputs[3];
			channels[chnIndex].hasPass = true;
		}
		else if (inputs[2] == "+o")
		{
			channels[chnIndex].chnOperators.push_back(inputs[3]);
		}
		else if (inputs[2] == "+n")
		{
			channels[chnIndex].modeN = true;
		}
	}
	else
	{
		msg = "You are not Admin";
		std::cout << msg << "\n";
		execute(send(client.fd, msg.c_str(), sizeof(msg.c_str()), 0), "ERR");
		return ;
	}
}