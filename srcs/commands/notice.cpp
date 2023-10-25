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

// void	Server::notice_command( Client &client )
// {
// 	std::cout << "NOTICE FONKSIYONU\n";
// 	std::string msg = getprefix(client);
// 	std::string dest = inputs[1];
// 	msg += ' ' + inputs[0] + ' ' + inputs[1] + ' ';
// 	for (unsigned long int l = 2; l < inputs.size(); l++){
// 		msg = msg + inputs[l];
// 		msg = msg + ' ';
// 	}
// 	msg += '\n';
// 	for (unsigned long int k = 0; k < clients.size() ; k++){
// 		if (!strncmp(dest.c_str(), (clients[k].nickName).c_str(), strlen(dest.c_str()))){
// 			send(clients[k].fd , msg.c_str(), msg.length(), 0);
// 			return;
// 		}
// 	}
// }
