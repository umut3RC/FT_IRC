#include "../../include/Server.hpp"

void	Server::pass_command( Client &client )
{
	commandMsg(client, "PASS");
	std::string	msg;
	for (unsigned long int i = 0; i < inputs.size(); i++)
	{
		if (inputs[i] == "PASS" && !client.passchk)
		{
			// std::cout << "IRC: Your pass->" << inputs[i + 1] << "<-\n";
			// std::cout << strncmp(inputs[i + 1].c_str(), serverPass.c_str(), strlen(serverPass.c_str())) << ">->servpass->" << serverPass << "<->" << inputs[i + 1] << "<<<-\n";
			// if (!strncmp(inputs[i + 1].c_str(), serverPass.c_str(), strlen(serverPass.c_str())))
			if (inputs[i + 1] ==  serverPass)
			{
				client.passchk = true;
				client.cltPass = inputs[i + 1];
				std::cout << "IRC: Password is correct.\n";
				// msg =ERR_PASSWDMISMATCH(getprefix(client));
				// execute(send(client.fd, msg.c_str(), msg.length(), 0), "Pass", 0);
			}
			else
			{
				msg = ERRserverPassMISMATCH(client.nickName);
				msg += "\r\n";
				std::cout << "IRC: Password incorrect!\n";
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "Pass", 0);
				// quit_command(client);
				return;
			}
		}
	}
	// std::string	msg;
	// if (this->serverPass == client.cltPass)
	// {
	// 	client.status = 1;
	// }
	// else
	// 	client.status = 0;
	// for (unsigned long int i = 0; i < inputs.size(); i++)
	// {
	// 	if (inputs[i] == "PASS")
	// 	{
	// 		if (inputs[i + 1] != serverPass)
	// 		{
	// 			msg = ERRserverPassMISMATCH(client.nickName);
	// 			msg += "\r\n";
	// 			std::cout << "IRC: Password incorrect!\n";
	// 			execute(send(client.fd, msg.c_str(), msg.length(), 0), "Pass", 0);
	// 			quit_command(client);
	// 		}
	// 		else
	// 		{
	// 			client.passchk = true;
	// 			client.cltPass = inputs[i + 1];
	// 			std::cout << "IRC: Password is correct.\n";
	// 			// msg =ERR_PASSWDMISMATCH(getprefix(client));
	// 			// execute(send(client.fd, msg.c_str(), msg.length(), 0), "Pass", 0);
	// 		}
	// 	}
	// }
}