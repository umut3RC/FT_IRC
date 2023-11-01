#include "../include/utils.hpp"

std::vector<std::string> splitString(const std::string& input, char delimiter)
{
	std::vector<std::string> result;
	std::string token;
	for (size_t i = 0; i < input.length(); ++i) {
		if (input[i] != delimiter) {
			token += input[i];
		} else {
			result.push_back(token);
			token.clear();
		}
	}
	result.push_back(token);
	return result;
}

void	Server::printInputs( void )
{
	for (int i = 0; i < (int)inputs.size(); i++)
		std::cout << "INP ->> " << inputs[i] << " <<-\n";
}

void	Server::commandMsg(Client client, std::string comd)
{
	std::cout << "IRC( "<< client.fd << " ): "<< comd <<" command" << std::endl;
}
int	Server::findMe(Client &client)
{
	int i = -1;
	while(i < (int)channels.size())
	{
		if (channels[i].chnName == client.nickName)
			return (i);
		i++;
	}
	return (i);
}

void	signalHandler( int s )
{
	std::cout << "Bye!\n";
	exit(s);
}

std::string	strCleaner(std::string s)
{
	return (s.erase(s.find_last_not_of(" \n\r\t")+1));
}

void	ToLower(std::string &s)
{
	for (int i=0; s[i]; i++)
		s[i] = tolower(s[i]);
}

void	ToUpper(std::string &s)
{
	for (int i=0; s[i]; i++)
		s[i] = toupper(s[i]);
}

/*
	0 ERR_MSG: "Failed to send in " + err +" command"
	1 ERR_MSG: "Failed to creat in " + err"
	2 ERR_MSG: "Failed to send in " + err
	3 ERR_MSG: error message
*/
void	execute(int ret, std::string err, int ERR_MSG)
{
	std::string err_mess[4];
	err_mess[0] = "Failed to send in " + err + " command!\n";
	err_mess[1] = "Failed to creat in " + err + "\n";
	err_mess[2] = "Failed to send in " + err + "\n";
	err_mess[3] = err;

	if (ret < 0 && ERR_MSG < 4 && ERR_MSG > -1)
	{
		throw std::runtime_error(err_mess[ERR_MSG]);
	}
	if (ret < 0)
		throw std::runtime_error(err);
}

int	Server::GetClientFdFromName(std::string targetName, int fd)
{
	// std::vector<Client>::iterator it = clients.begin();
	// while (it != clients.end())
	// {
	// 	if (!strncmp(it->nickName.c_str(), targetName.c_str(), strlen(targetName.c_str())) && it->fd != fd)
	// 		return (it->fd);
	// 	it++;
	// }
	// std::cout << "IRC: No client in this name.\n";
	// return (-1);
	for (unsigned long int i = 0; i < clients.size(); i++)
	{
		if (!strncmp(targetName.c_str(), clients[i].nickName.c_str(), targetName.length())
			&&clients[i].fd != fd)
		{
			std::cout << "IRC: Client is finded.\n";
			return (clients[i].fd);
		}
	}
	std::cout << "IRC: No client in this name.\n";
	return (-1);
}

int	Server::GetChannelFromName(std::string targetName)
{
	// for (int i = 0; i < (int)channels.size(); i++)
	// {
	// 	if (!strncmp(channels[i].chnName.c_str(), targetName.c_str(), strlen(targetName.c_str())))
	// 	{ 
	// 		std::cout << "IRC: Channel is finded.\n";
	// 		return(i);
	// 	}
	// }
	// std::cout << "IRC: Channel is not finded.\n";
	// return (-1);

	for (unsigned long int i = 0; i < channels.size(); i++)
	{
		if (!strncmp(targetName.c_str(), channels[i].chnName.c_str(), targetName.length()))
		{
			std::cout << "IRC: Channel is finded.\n";
			return (i);
		}
	}
	std::cout << "IRC: Channel is not finded.\n";
	return (-1);
}

int	Server::GetClientIndexFromName(std::string target)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
		if (clients[i].nickName == target)
			return (i);
	}
	return (-1);
}

bool	Channel::isOperator( std::string s)
{
	for(int i = 0; i < (int)chnOperators.size(); i++)
	{
		if (chnOperators[i] == s)
		{
			std::cout << "IRC: Client is an operator.\n";
			return (true);
		}
	}
	std::cout << "IRC: Client is NOT an operator.";
	return (false);
}

void	Channel::eraseClient(std::string nick)
{
	for (int i = 0; i < (int)this->chnClients.size(); i++)
	{
		if (!strncmp(this->chnClients[i].nickName.c_str(), nick.c_str(), nick.length()))
		{
			this->chnClients.erase(this->chnClients.begin() + i);
			this->chnClientsNum--;
			break;
		}
	}
}
void	Channel::brodcastMsg(std::string msg)
{
	for (int i = 0; i < this->chnClientsNum; i++)
		execute(send(this->chnClients[i].fd, msg.c_str(), msg.length(), 0), "brodcast", 2);
}

bool	Channel::isClientHere( std::string c )
{
	for (int i = 0; i < (int)chnClients.size(); i++)
	{
		if (chnClients[i].nickName == c)
			return (true);
	}
	return (false);
}
