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
