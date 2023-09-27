#include "../../include/Server.hpp"

void	Server::tester(Client &client)
{
	std::cout << "IRC: Called TESTER command\n";
	for (int i = 0; i < (int)inputs.size(); i++)
	{
		std::cout << "Inputs: " << inputs[i] << "\n";
	}
	std::cout << "Client fd: " << client.fd << "\n";
	std::cout << "Client nick: " << client._nickName << "\n";
	std::cout << "Client user: " << client._userName << "\n";
	std::cout << "Client user: " << client._userName << "\n\n";
	std::vector<Client>::iterator it = clients.begin();
	while (it != clients.end())
	{
		std::cout << "C: " << it->_nickName << "\n";
		it++;
	}
}