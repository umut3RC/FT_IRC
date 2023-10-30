#include "../../include/Server.hpp"

void	Server::notice_command( Client &client )
{
	commandMsg(client, "NOTICE");
	std::string msg = getprefix(client);
	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
	for (int i = 2; i < (int)inputs.size(); i++)
	{
		msg = msg + inputs[i];
		msg = msg + ' ';
	}
	msg = msg + "\r\n";
	execute(send(GetClientFdFromName(inputs[1], client.fd) , msg.c_str(), msg.length(), 0), "Notice", 0);
}
