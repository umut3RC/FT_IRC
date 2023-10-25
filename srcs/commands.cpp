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
	for (unsigned long int i = 0; i < inputs.size(); i++)
	{
		if (inputs[i] == "PASS")
		{
			client.passchk = true;
			if (atoi(inputs[i + 1].c_str()) != serverPass)
			{
				msg = ERRserverPassMISMATCH(client.nickName);
				send(client.fd, msg.c_str(), msg.length(), 0);
				quit_command(client);
			}
		}
	}
	// printInputs();
	// if (!client.passchk || client.nickName.empty())
	// 	quit_command(client);
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
