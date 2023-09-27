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
	// commands["NOTICE"]	= &Server::notice;			//yok erdem
	// commands["MODE"]	= &Server::mode;			//yok erdem
	// commands["WHO"]		= &Server::who;				//yok erdem
	//commands["KICK"]	= &Server::kick;			//yok umut
	//commands["PART"]	= &Server::part;			//yok umut
	commands["CAP"] = &Server::cap_command;
	commands["QUIT"] = &Server::quit_command;
	commands["USER"] = &Server::user_command;
	commands["JOIN"] = &Server::join_command;
	commands["PING"] = &Server::ping_command;
	commands["NICK"] = &Server::nick_command;
	commands["PASS"] = &Server::pass_command;
	commands["PRIVMSG"] = &Server::privmsg_command;
	commands["TESTER"] = &Server::tester;
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
			if (atoi(inputs[i + 1].c_str()) != _passwd)
			{
				msg = "ERROR! Password incorrect\n";
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
		if (inputs[i] == "KICK")
			std::cout << "IRC kick\n";
		if (inputs[i] == "MODE")
			std::cout << "IRC mode\n";
		if (inputs[i] == "INVITE")
			std::cout << "IRC invite\n";
		if (inputs[i] == "NOTICE")
			std::cout << "IRC notice\n";
	}
	inputs.clear();
}
