/*
john_doe is John Doe
john_doe is using irc.example.com
john_doe has been idle 30 minutes
john_doe is a registered user
End of WHOIS list.
*/

#include "../../include/Server.hpp"

void	Server::whois_command( Client &client )
{
	commandMsg(client, "WHOIS");
	std::string msg = getprefix(client);
	int target = GetClientIndexFromName(inputs[1]);
	if (inputs.size() < 2)
	{
		msg = ERR_NEEDMOREPARAMS(getprefix(client), "Whois");
		msg += "\r\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Whois", 0);
		return;
	}
	if (target < 0)
	{
		std::cout << "IRC: Client is not online.\n";
		throw std::runtime_error("IRC: Client is not online.\n");
	}
	msg = msg + " WHOIS\n" + clients[target].nickName + " is " + clients[target].userName + "\n";
	msg = msg + clients[target].nickName + " is using " + clients[target].host + "\n";
	msg = msg + clients[target].nickName + " is a registered user\n";
	msg = msg + "End of WHOIS list.\r\n";
	execute(send(client.fd, msg.c_str(), msg.length(), 0), "Whois", 0);
}