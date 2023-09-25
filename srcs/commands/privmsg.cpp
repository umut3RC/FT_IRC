#include "../../include/Server.hpp"

/*
target user
message
message
message
...
*/

int	Server::GetClientFdFromName(std::string targetName)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
		std::cout << "inCfind\n";
		std::cout << "target-> " << targetName << '\n';
		std::cout << "Cname-> " << clients[i]._nickName << '\n';
		std::cout << "compare = " << clients[i]._nickName.compare(targetName) << '\n';
		if (clients[i]._nickName == targetName)
		{
			std::cout << "finded\n";
			return(clients[i].fd);
		}
	}
	return (-0);
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

void Server::privmsg_command(Client &client)
{
	std::cout << "IRC: PRIVMSG command\n";
	(void)client;
	int	targetFd;
	std::string	msg;

	targetFd = GetClientFdFromName(inputs[1]);
	if (targetFd < 0)
	{
		// if(!GetClientFdFromName(inputs[1]))
		// {
			std::cout << "IRC: User(" << inputs[1] << ") is not finded\n";
			msg = "User is not finded!\n";
			execute(send(targetFd, msg.c_str(), sizeof(msg), 0), "Err\n");
		// }
	}
	for (int i = 2; i < (int)inputs.size(); i++)
	{
	msg = msg + " " + inputs[i];
	}
	msg[(int)msg.size()] = '\0';
	execute(send(targetFd, msg.c_str(), sizeof(msg), 0), "Err\n");
}
