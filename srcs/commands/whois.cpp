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
	commandMsg(client, "NOTICE");
	std::string msg = getprefix(client);
	int target = GetClientIndexFromName(inputs[1]);
	if (target < 0)
	{
		std::cout << "IRC: Client is not online.\n";
		throw std::runtime_error("IRC: Client is not online.\n");
	}
	// msg = clients[target].nickName + " is " + clients[target].userName + "\n";
	// msg = msg + clients[target].nickName + " is using " + clients[target].host + "\n";
	// msg = msg + clients[target].nickName + " is a registered user\n";
	// msg = msg + "End of WHOIS list.\n";
	// std::cout << msg << std::endl;

	msg = getprefix(clients[target]) + " 352 " + clients[target].nickName + " " + inputs[1];
            msg += " " + clients[target].userName;
            msg += " " + clients[target].userName;
            msg += " " + getprefix(clients[target]);
            msg += " " + clients[target].nickName;
            msg += " H";
            msg += ":0 " + clients[target].userName;

	// PRIVMSG Hedef :Mesaj
	// msg = "PRIVMSG " + client.nickName + " :" + msg;
	execute(send(GetClientFdFromName(inputs[1], client.fd), msg.c_str(), msg.length(), 0), "Whois", 0);
	// execute(send(GetClientFdFromName(inputs[1], client.fd), msg.c_str(), sizeof(msg.c_str()), 0), "ERR\n");
}