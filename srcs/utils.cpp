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
	result.push_back(token); // Son kelimeyi ekle
	return result;
}

void	Server::printInputs( void )
{
	for (int i = 0; i < (int)inputs.size(); i++)
		std::cout << "INP: " << inputs[i] << "\n";
}

void	Server::commandMsg(Client client, std::string comd)
{
	std::cout << "IRC( "<< client.fd << " ): "<< comd <<" command" << std::endl;
}
int	Server::findMe(Client &client)
{
	for (int i = 0; i < (int)channels.size(); i++)
	{
		if (channels[i].chnName == client.nickName)
			return (i);
	}
	return (i);
}

void	signalHandler( int s )
{
	std::cout << "Bye!\n";
	exit(s);
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

void	execute(int ret, std::string err)
{
	if (ret < 0)
		throw std::runtime_error(err);
}
