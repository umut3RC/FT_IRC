#include "../include/utils.hpp"

void	checkServerCommands(std::string cmd)
{
	if (cmd.substr(0, 6) == "JOIN #")
		std::cout << "You want join a channel(  ), right?\n";
}