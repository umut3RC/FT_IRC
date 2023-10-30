#include "../include/utils.hpp"

void	Server::commandHandler( void )
{
	char* str = strtok(buffer, " \n");
	while (str != NULL)
	{
		inputs.push_back(str);
		str = strtok(NULL, " \n");
	}
}

void	Server::setCommands()
{
	commands["QUIT"] = &Server::quit_command;//			(1)
	commands["CAP"] = &Server::cap_command;//			(2)
	commands["NICK"] = &Server::nick_command;//			(3)
	commands["USER"] = &Server::user_command;//			(4)
	commands["PRIVMSG"] = &Server::privmsg_command;//	(5)
	commands["JOIN"] = &Server::join_command;//			(6)
	commands["PING"] = &Server::ping_command;//			(7)
	commands["PASS"] = &Server::pass_command;//			(8)
	commands["MODE"] = &Server::mode_command;//			(9)
	commands["PART"] = &Server::part_command;//			(10)
	commands["NOTICE"] = &Server::notice_command;//		(11)
	commands["WHOIS"] = &Server::whois_command;//		(12)
	commands["KICK"] = &Server::kick_command;//			(13)
	commands["INVITE"] = &Server::invite_command;//		(14)
	commands["GODMODE"] = &Server::godmode;//			(*_*)
}

void Server::runCommand(Client &client)
{
	std::string msg;
	ToUpper(inputs[0]);
	if (!clientAuthentication(client))
	{
		msg = "IRC: Authentication failed!\nYou need pass and nick name.\nUse this format for first connect to server(Without '<','>'):\nPASS <server_pass> NICK <your nick name>\r\n";
		std::cout << msg;
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Cant Sended on commands!\n", 3);
		// inputs.clear();
		return;
	}
	for(unsigned long int i = 0; i < inputs.size(); i++)
	{
		std::map<std::string, void(Server::*)(Client &client)>::iterator itCF;
		for (itCF = commands.begin(); itCF != commands.end(); ++itCF)
		{
			if (!itCF->first.compare(inputs[i]))
			{
				(this->*(itCF->second))(client);
			}
		}
	}
	inputs.clear();
}
