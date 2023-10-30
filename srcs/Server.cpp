#include "../include/Server.hpp"

static bool	ret = false;

Server::Server( const Server &src )
{*this = src;}

Server::~Server( void )
{
	std::cout << "IRC: Server closed. Have a good day!\n";
	for (int i = 0; i < (int)pollFd.size(); i++)
		close(pollFd[i].fd);
	close(serverSockFd);
}

Server::Server( char **av )
{
	std::cout << "*-\\______________________/-*\n";
	std::cout << "|   IRC Server Starting    |\n";
	std::cout << "*_/----------------------\\_*\n";
	serverPort = std::atoi(av[1]);
	serverPass = av[2];
	serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
	serverClntNum = 0;
	serverChnNum = 0;
	// inputs[0] = "IRCSERV";
	setCommands();
	if (serverSockFd == -1)
		throw std::runtime_error("Error!\nSocket could not be created!\n");
	else
		std::cout << "IRC: Socket created successfully!\n";

	// SILINECEK-V_V_V_V_V_V_V_V_V_V_V
	int val = 1;
	setsockopt(this->serverSockFd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	// SILINECEK-^_^_^_^_^_^_^_^_^_^_^
}

void	Server::sstart( void )
{
	signal(SIGINT, signalHandler);
	std::cout << "IRC: Socket connecting.\n";
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(serverPort);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	execute(bind(serverSockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)), "Error!\nBind the server socket failed\n", 3);

	execute(listen(serverSockFd, 10), "Error!\nListening failed\n", 3);
	std::cout << "IRC: Listening on port " << serverPort << std::endl;
	Poll();
	loop();
}

std::string Server::getprefix(Client &client)
{
	std::string msg = ':' + client.nickName + '!' + client.userName;
	if (!client.host.empty())
		msg += '@' + client.host;
	return (msg);
}

int	Server::addNewClient(pollfd pfd, Client client, int clientSockFd)
{
	pfd.fd = clientSockFd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	pollFd.push_back(pfd);
	clients.push_back(client);
	clients[serverClntNum].fd = clientSockFd;
	clients[serverClntNum].isFirstNickAssigment = false;
	clients[serverClntNum].passchk = false;
	clients[serverClntNum].status = 2;
	std::cout << "IRC: New client connected.\n";
	// std::string msg = getprefix(client) + " :Welcome To (I)nternet (R)elay (C)hat\r\n";
	// execute(send(client.fd, msg.c_str(), msg.length(), 0), "The new client is can not added!\n", 3);
	return (1);
}

void	Server::loop( void )
{
	Client	client;
	pollfd	pfd;
	int	clientSockFd;
	int	retRead;
	while (1)
	{
		if (poll(pollFd.data(), pollFd.size(), 0) == -1)
			throw std::runtime_error("Error!\npoll didn't listen.\n");
		for (size_t i = 0; i < pollFd.size(); ++i)
		{
			if (pollFd[i].revents & POLLHUP)
			// if (pollFd[i].revents & (POLLHUP | POLLERR))
			{
				quit_command(clients[i - 1]);
				break;
			}
			if (pollFd[i].revents & POLLIN)
			{
				if (pollFd[i].fd == serverSockFd)
				{
					clientSockFd = accept(serverSockFd, NULL, NULL);
					if (clientSockFd == -1)
						throw std::runtime_error("Error!\nAccepting client can not connection\n");
					serverClntNum += addNewClient(pfd, client, clientSockFd);
				}
				else
				{
					retRead = recv(pollFd[i].fd, buffer, sizeof(buffer), 0);
					if (retRead == -1)
						throw std::runtime_error("Error!\nCan't read from the client.\n");
					else if (retRead == 0)
					{
						std::cerr << "IRC: Client connection closed." << std::endl;
						quit_command(clients[i - 1]);
						return;
					}
					else
					{
						buffer[retRead] = '\0';
						try
						{
							commandHandler();
							runCommand(clients[i - 1]);
						}
						catch(const std::exception &e){
							std::cout << e.what() << std::endl;
						}
					}
				}
			}
		}
	}
}

void	Server::Poll( void )
{
	pollfd	myPoll;
	memset(&myPoll, 0, sizeof(myPoll));//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	myPoll.fd = serverSockFd;
	myPoll.events = POLLIN;
	pollFd.push_back(myPoll);
}

bool	Server::clientAuthentication(Client client)
{
	std::string	firstCmds[4];
	firstCmds[0] = "CAP";
	firstCmds[1] = "PASS";
	firstCmds[2] = "NICK";
	firstCmds[3] = "USER";
	std::map<std::string, void(Server::*)(Client &client)>::iterator itCF;
	if (!ret || !client.passchk || client.nickName.empty())
	{
		for (int j = 0; j < (int)inputs.size(); j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (inputs[j] == firstCmds[i])
				{
					for (itCF = commands.begin(); itCF != commands.end(); ++itCF)
					{
						if (!itCF->first.compare(firstCmds[i]))
						{
							(this->*(itCF->second))(client);
							break;
						}
					}
				}
			}
		}
	}
	// std::cout << client.passchk << "<-*->" << client.nickName.empty() << "<-\n";
	if (client.passchk && !client.nickName.empty())
		ret = true;
	return (ret);
}

Server	&Server::operator=( const Server &src)
{
	this->serverPort = src.serverPort;
	this->serverPass = src.serverPass;
	this->serverSockFd = src.serverSockFd;
	this->serverClntNum = src.serverClntNum;
	this->serverChnNum = src.serverChnNum;
	return (*this);
}


