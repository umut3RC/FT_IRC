
#include "../../include/Server.hpp"

void	Server::notice_command( Client &client )
{
	commandMsg(client, "NOTICE");
	std::string msg = getprefix(client);
	std::string target = inputs[1];
	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
	for (unsigned long int l = 2; l < inputs.size(); l++){
		msg = msg + inputs[l];
		msg = msg + ' ';
	}
	msg += '\n';
	execute(send(GetClientFdFromName(target, client.fd), msg.c_str(), sizeof(msg.c_str()), 0), "ERR\n");
}