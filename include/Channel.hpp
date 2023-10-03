#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Client;

class Channel
{
private:
public:
	std::string					chnName;
	std::string					chnPass;
	std::string					chnAdmin;
	std::vector<std::string>	chnOperators;
	std::vector<std::string>	whiteList;
	std::vector<Client>			chnClients;
	int							maxUser;
	int							chnClientsNum;
	bool						hasPass;
	bool						modeN;
	bool						ifp;

	Channel(std::string name) : chnName(name) {chnClientsNum = 0; hasPass = 0; maxUser = 0; modeN = 0; ifp = 0;};
};

#endif