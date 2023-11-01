#include "../../include/Server.hpp"

void	Server::notice_command( Client &client )
{
	commandMsg(client, "NOTICE");
	std::string msg = getprefix(client);
	int	targetFd = GetClientFdFromName(inputs[1], client.fd);
	if (inputs.size() < 2)
	{
		msg = ERR_NEEDMOREPARAMS(getprefix(client), "Notice");
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Notice", 0);
	}
	msg += ' ' + inputs[0] + ' ' + targetFd + ' ';
	for (int i = 2; i < (int)inputs.size(); i++)
	{
		msg = msg + inputs[i];
		msg = msg + ' ';
	}
	msg = msg + "\r\n";
	if ()
	execute(send(targetFd , msg.c_str(), msg.length(), 0), "Notice", 0);
}
