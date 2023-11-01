#include "../../include/Server.hpp"

void	Server::notice_command( Client &client )
{
	commandMsg(client, "NOTICE");
	std::string msg = getprefix(client);
	int	targetFd = GetClientFdFromName(inputs[1], client.fd);
	if (inputs.size() < 2)
	{
		msg = ERR_NEEDMOREPARAMS(getprefix(client), "Notice");
		msg += "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Notice", 0);
		return;
	}
	if (targetFd < 0)
		return;
	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
	for (int i = 2; i < (int)inputs.size(); i++)
	{
		msg = msg + inputs[i];
		msg = msg + ' ';
	}
	msg = msg + "\r\n";
	execute(send(targetFd , msg.c_str(), msg.length(), 0), "Notice", 0);
}
