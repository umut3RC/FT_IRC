#include "../include/utils.hpp"

void	Server::commandHandler( void )
{
	char* str = strtok(buffer, " \r\n");
	inputs.clear();
	while (str != NULL)
	{
		inputs.push_back(strCleaner(str));
		str = strtok(NULL, " \n");
	}
}

void	Server::setCommands()
{
	commands["QUIT"] = &Server::quit_command;
	commands["CAP"] = &Server::cap_command;
	commands["NICK"] = &Server::nick_command;
	commands["USER"] = &Server::user_command;
	commands["PRIVMSG"] = &Server::privmsg_command;
	commands["JOIN"] = &Server::join_command;
	commands["PING"] = &Server::ping_command;
	commands["PASS"] = &Server::pass_command;
	commands["MODE"] = &Server::mode_command;
	commands["PART"] = &Server::part_command;
	commands["NOTICE"] = &Server::notice_command;
	commands["WHOIS"] = &Server::whois_command;
	commands["KICK"] = &Server::kick_command;
	commands["INVITE"] = &Server::invite_command;
}

void Server::runCommand(Client &client)
{
	std::string msg;
	ToUpper(inputs[0]);
	printInputs();
	if (!clientAuthentication(client))
	{
		msg = "IRC: Authentication failed!\nYou need pass and nick name.\nUse this format for first connect to server(Without '<','>'):\nPASS <server_pass> NICK <your nick name>\r\n";
		std::cout << msg;
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Cant Sended on commands!\n", 3);
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
