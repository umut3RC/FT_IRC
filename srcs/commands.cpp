#include "../include/utils.hpp"

void	Server::commandHandler( void )
{
	int	i;

	i = 0;
	char* str = strtok(buffer, " \n");
	while (str != NULL)
	{
		inputs.push_back(str);
		i++;
		str = strtok(NULL, " \n");
	}
}

void	Server::setCommands()
{
	//commands["PART"]	= &Server::part;			//yok umut
	commands["CAP"] = &Server::cap_command;//			(1)
	commands["QUIT"] = &Server::quit_command;//			(2)
	commands["USER"] = &Server::user_command;//			(3)
	commands["JOIN"] = &Server::join_command;//			(4)
	commands["PING"] = &Server::ping_command;//			(5)
	commands["NICK"] = &Server::nick_command;//			(6)
	commands["PASS"] = &Server::pass_command;//			(7)
	commands["PRIVMSG"] = &Server::privmsg_command;//	(8)
	commands["TESTER"] = &Server::tester;
	commands["MODE"] = &Server::mode_command;//			(9)
	// commands["PART"] = &Server::part_command;//			(10)
	commands["NOTICE"] = &Server::notice_command;//		(11)
	commands["WHOIS"] = &Server::whois_command;//		(12)
	commands["KICK"] = &Server::kick_command;//			(13)
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
	for(unsigned long int i = 0; i < inputs.size(); i++)
	{
		std::map<std::string, void(Server::*)(Client &client)>::iterator itCF;
		// std::cout << ">>>" << inputs[i] << "<<<\n";
		for (itCF = commands.begin(); itCF != commands.end(); ++itCF)
		{
			if (!itCF->first.compare(inputs[i]))
			{
				(this->*(itCF->second))(client);
			}
		}
		if (inputs[i] == "PART")
			std::cout << "IRC kick\n";
		if (inputs[i] == "INVITE")
			std::cout << "IRC invite\n";
	}
	inputs.clear();
}
