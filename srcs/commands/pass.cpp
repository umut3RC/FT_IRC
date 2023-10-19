#include "../../include/Server.hpp"

void	Server::pass_command( Client &client )
{
	commandMsg(client, "PASS");
	// for (int i = 0; i < (int)inputs.size(); i++)
	// {
	// 	std::cout << i << ": " << inputs[i] << "\n";
	// }
	// try
	// {
	// 	// client.c_pass = inputs.at(1);
	// 	// client.userName = inputs.at(2);
	// 	// client.userName = inputs.at(2);
	// 	// client.host = inputs.at(5);
	// }
	// catch(const std::out_of_range &e)
	// {
	// 	std::string msg = ERR_NEEDMOREPARAMS(getprefix(client), inputs[0]);
	// 	execute(send(client.fd, msg.c_str(), msg.size(), 0), "sa");
	// }
	std::string	msg;
	if (this->serverPass == client.c_pass)
	{
		client.status = 1;
	}
	else
		client.status = 0;
	for (unsigned long int i = 0; i < inputs.size(); i++)
	{
		if (inputs[i] == "PASS")
		{
			client.passchk = true;
			if (atoi(inputs[i + 1].c_str()) != serverPass)
			{
				msg = ERRserverPassMISMATCH(client.nickName);
				execute(send(client.fd, msg.c_str(), msg.length(), 0), "ERR_PASS\n");
				quit_command(client);
			}
		}
	}
}