#include "../../include/Server.hpp"

void	Server::godmode(Client &client)
{
	commandMsg(client, "godmode");
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
		std::cout << "Clt: " << it->nickName << "\n";
		it++;
	}
	std::vector<Channel>::iterator it2 = channels.begin();
	while (it2 != channels.end())
	{
		std::cout << "Chn: " << it2->chnName << "\n";
		it2++;
	}
}