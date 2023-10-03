#include "../../include/Server.hpp"

void	Server::tester(Client &client)
{
	commandMsg(client, "TESTER");
	for (int i = 0; i < (int)inputs.size(); i++)
	{
		std::cout << "Inputs: " << inputs[i] << "\n";
	}
	std::cout << "Client fd: " << client.fd << "\n";
	std::cout << "Client nick: " << client.nickName << "\n";
	std::cout << "Client user: " << client.userName << "\n";
	std::cout << "Client user: " << client.userName << "\n\n";
	std::vector<Client>::iterator it = clients.begin();
	while (it != clients.end())
	{
		std::cout << "C: " << it->nickName << "\n";
		it++;
	}
}