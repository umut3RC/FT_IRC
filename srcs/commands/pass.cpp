#include "../../include/Server.hpp"

void	Server::pass_command( Client &client )
{
	std::cout << "IRC: Called PASS command\n";
	// for (int i = 0; i < (int)inputs.size(); i++)
	// {
	// 	std::cout << i << ": " << inputs[i] << "\n";
	// }
	// try
	// {
	// 	// client.c_pass = inputs.at(1);
	// 	// client._userName = inputs.at(2);
	// 	// client._userName = inputs.at(2);
	// 	// client._host = inputs.at(5);
	// }
	// catch(const std::out_of_range &e)
	// {
	// 	std::string msg = ERR_NEEDMOREPARAMS(getprefix(client), inputs[0]);
	// 	execute(send(client.fd, msg.c_str(), msg.size(), 0), "sa");
	// }
	if (this->_passwd == client.c_pass)
		client.status = 1;
	else
		client.status = 0;
}