#include "../../include/Server.hpp"

void	Server::part_command( Client &client )
{
	commandMsg(client, "PART");
	// printInputs();
	commands["QUIT"](client);
}