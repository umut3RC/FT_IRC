#include "../../include/Server.hpp"

void	Server::pass_command( Client &client )
{
	commandMsg(client, "PASS");
	std::string	msg;
	if (inputs.size() < 2)
	{
		msg = ERR_NEEDMOREPARAMS(getprefix(client), "Join");
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Join", 0);
		return;
	}
	for (unsigned long int i = 0; i < inputs.size(); i++)
	{
		if (inputs[i] == "PASS" && !client.passchk)
		{
			inputs[i + 1] = strCleaner(inputs[i + 1]);
			if (inputs[i + 1] ==  serverPass)
			{
				client.passchk = true;
				client.cltPass = inputs[i + 1];
				std::cout << "IRC: Password is correct.\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Pass", 0);
			}
			else
			{
				msg = ERRserverPassMISMATCH(client.nickName);
				msg += "\r\n";
				std::cout << "IRC: Password incorrect!\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Pass", 0);
				return;
			}
		}
	}
}
