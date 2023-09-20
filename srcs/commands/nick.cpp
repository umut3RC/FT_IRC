#include "../../include/Server.hpp"

void	Server::nick_command( Client &client )
{
	std::cout << "IRC: Called NICK command\n";
	for (int i = 0; i < (int)inputs.size(); i++)
	{
		std::cout << i << ": " << inputs[i] << "\n";
	}
	try
	{
		client._nickName = inputs.at(1);
		client._userName = inputs.at(2);
		client._host = inputs.at(5);
		std::string msg = ": NICK " + client._nickName + "@" + client._host;
		execute(send(client.fd, msg.c_str(), sizeof(msg), 0), "ERR");
		cout << msg
	}
	catch(const std::out_of_range &e)
	{
		execute(send(client.fd, "out_of_range", strlen("out_of_range"), 0), "out_of_range");
		//"461 " + prefix + " " +  command + " :Not enough parameters"
	}
}
