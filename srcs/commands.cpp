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
	commands["QUIT"] = &Server::quit_command;
	commands["CAP"] = &Server::cap_command;
	commands["USER"] = &Server::user_command;
	commands["JOIN"] = &Server::join_command;
	// commands["QUIT"] = &Server::quit_command;
	// commands["NICK"] = &Server::nick;
	// commands["PASS"] = &Server::pass;
	// commands["USER"] = &Server::user;
	// commands["KICK"] = &Server::kick;
	// commands["PART"] = &Server::part;
	// commands["PING"] = &Server::ping;
	// commands["PRIVMSG"] = &Server::privmsg;
	// commands["NOTICE"] = &Server::notice;
	// commands["MODE"] = &Server::mode;
	// commands["WHO"] = &Server::who;
}

void Server::runCommand(Client &client)
{
	std::string msg;
	ToUpper(inputs[0]);
	if (sizeof(client) < 1)
		std::cout << "hmm\n";
	// for (unsigned long int i = 0; i < inputs.size(); i++){
	// 	if (inputs[i] == "PASS"){
	// 		client.passchk = true;
	// 		if (atoi(inputs[i + 1].c_str()) != _passwd){
	// 			msg = "ERROR! Password incorrect\n";
	// 			send(client.fd, msg.c_str(), msg.length(), 0);
	// 			msg.clear();
	// 			quit_command(client);
	// 		}
	// 	}
	// }
	for(unsigned long int i = 0; i < inputs.size(); i++)
	{
		std::cout << inputs[i] << "<------------------commandssssssss\n";
		commands[inputs[i]];
		if (inputs[i] == "NICK")
			std::cout << "IRC nick\n";
		if (inputs[i] == "PRIVMSG")
			std::cout << "IRC privmsg\n";
		if (inputs[i] == "PING")
			std::cout << "IRC ping\n";
		if (inputs[i] == "PASS")
			std::cout << "IRC pass\n";
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
