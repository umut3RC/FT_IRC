#include "../include/Server.hpp"

Server::Server( const Server &src )
{*this = src;}

Server::~Server( void )
{
	std::cout << "IRC: Server closed. Have a good day!\n";
	close(_sockfd);
}

Server::Server( char **av )
{
	std::cout << "IRC: Socket starting . . .\n";
	_port = std::atoi(av[1]);
	_passwd = std::atoi(av[2]);
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	_srvClientNum = 0;
	_chNum = 0;
	if (_sockfd == -1)
		throw std::runtime_error("Error!\nSocket could not be created!\n");
	else
		std::cout << "IRC: Socket created successfully!\n";
}

void	Server::sstart( void )
{
	signal(SIGINT, signalHandler);
	std::cout << "IRC: Socket connecting.\n";
	_sockAddr.sin_family = AF_INET;	//soket adresinin aile türünü belirtir. Burada AF_INET, IPv4 adres ailesini temsil eder. Sunucu, bu aile türünü kullanarak IPv4 adresleri ile iletişim kurar.
	_sockAddr.sin_port = htons(_port);	//sunucunun hangi port üzerinden bağlantıları dinleyeceğini belirtir. Burada htons işlevi (host to network short), 16 bitlik bir değeri ağ baytlarına (network byte order) dönüştürür. Bu nedenle 8080 portunu ağ baytlarına dönüştürerek kullanılır.
	_sockAddr.sin_addr.s_addr = INADDR_ANY;	//sunucunun hangi IP adresini dinleyeceğini belirtir. INADDR_ANY, sunucunun mevcut tüm ağ arayüzleri üzerinden gelen bağlantıları kabul edeceği anlamına gelir. Bu, sunucunun herhangi bir IP adresi ile gelen bağlantıları dinlemesini sağlar ve bu şekilde sunucunun herhangi bir ağ arabirimi veya IP adresine bağlanmasına izin verir.

	// Sunucu soketini bağlama
	if (bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr)) == -1)
	{
		throw std::runtime_error("Error!\n Bind the server socket failed\n");
		// close(client._clientFd);
		// close(_sockfd);
		// bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr));
	}

	if (listen(_sockfd, 10) == -1)
		throw std::runtime_error("Error!\n Listening failed\n");
	std::cout << "IRC: Listening on port " << _port << std::endl;
	// client._clientFd = accept(_sockfd, (struct sockaddr *)&client._clientAddr, sizeof(client._clientAddr));
	
	Poll();
	loop();
	
	// client._clientFd = accept(_sockfd, NULL, NULL);
	// if (client._clientFd == -1)
	// 	throw std::runtime_error("Error!\nAccepting client connection.\n");
	// // İstemciden gelen veriyi okuma ve ekrana yazdırma
	// while (1)
	// {
	// 	std::vector<std::string> clientMsgSplit;
	// 	std::vector<std::string>::iterator clientMsgSplit_iter;
	// 	recv(client._clientFd, buffer, sizeof(buffer), 0);
	// 	// std::cout << "From client: " << buffer << std::endl;
	// 	// std::cout << ">>****>" << buffer << "<****<<";

	// 	clientMsgSplit = splitString(buffer, '\n');
	// 	clientMsgSplit_iter = clientMsgSplit.begin();
	// 	while (clientMsgSplit_iter != clientMsgSplit.end())
	// 	{
	// 		std::cout << ">>**>>" << *clientMsgSplit_iter << "<<**<<\n";
	// 		checkServerCommands(*clientMsgSplit_iter);
	// 		++clientMsgSplit_iter;
	// 	}
	// 	// İstemciye yanıt gönderme
	// 	// const char *response = "Hello from server!";
	// 	// send(client._clientFd, response, strlen(response), 0);
	// }	
	// Soketleri kapatma
	// close(client._clientFd);
	close(_sockfd);
}

std::string Server::getprefix(Client &client)
{
	std::string ret;
	ret = ':' + client._nickName + '!' + client._userName;
	if (!client._host.empty())
		ret += '@' + client._host;
	return (ret);
}

void	Server::loop( void )
{
	Client	client;
	pollfd	pfd;
	int	clientSockFd;
	int	retRead;
	while (1)
	{
		if (poll(pollFd.data(), pollFd.size(), -1) == -1)
			throw std::runtime_error("Error!\npoll didn't listen.\n");
		for (size_t i = 0; i < pollFd.size(); ++i)
		{
			if (pollFd[i].revents & POLLHUP)
			{
				quit(clients[i - 1]);
				break;
			}
			if (pollFd[i].revents & POLLIN)
			{
				if (pollFd[i].fd == _sockfd)
				{
					clientSockFd = accept(_sockfd, NULL, NULL);
					if (clientSockFd == -1)
						throw std::runtime_error("Error!\nAccepting client can not connection\n");
					pfd.fd = clientSockFd;
					pfd.events = POLLIN;
					pfd.revents = 0;
					pollFd.push_back(pfd);
					clients.push_back(client);
					clients[_srvClientNum].fd = clientSockFd;
					clients[_srvClientNum]._nickNamefirst = false;
					clients[_srvClientNum].passchk = false;
					clients[_srvClientNum].status = 2;
					_srvClientNum++;
					std::cout << "IRC: New client connected\n";
				}
				else
				{
					retRead = recv(pollFd[i].fd, buffer, sizeof(buffer), 0);
					if (retRead == -1)
						throw std::runtime_error("Error!\nCan't read from the client.\n");
					else if (retRead == 0)
					{
						std::cerr << "IRC: Client connection closed." << std::endl;
						quit(clients[i - 1]);
						return;
					}
					else
					{
						buffer[retRead] = '\0';
						clients[i - 1].num = i - 1;
						commandHandler();
						runCommand(clients[i - 1]);
					}
				}
			}
		}
	}
	// close(pollFd);
}

void	Server::Poll( void )
{
	pollfd	myPoll;
	memset(&myPoll, 0, sizeof(myPoll));// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	myPoll.fd = _sockfd;
	myPoll.events = POLLIN;
	pollFd.push_back(myPoll);
}

Server	&Server::operator=( const Server &src)
{
	this->_port = src._port;
	this->_passwd = src._passwd;
	this->_sockfd = src._sockfd;
	this->_srvClientNum = src._srvClientNum;
	this->_chNum = src._chNum;
	return (*this);
}

void	Server::quit(Client &client)
{
	std::vector<Client>::iterator it;

	std::cout << "-QUIT-\n";
	for (unsigned long int i = 0; i < channels.size(); i++)
	{
		for (unsigned long int j = 0 ; j < channels[i].chnclients.size(); j++)
		{
			if (channels[i].chnclients[j]._nickName == client._nickName)
			{
				if (channels[i]._admin == client._nickName)
				{
					std::cout << channels[i]._admin << '\n';
					it = channels[i].chnclients.begin() + i;
					it++;
					channels[i]._admin = it->_nickName;
					std::cout << channels[i]._admin << '\n';
				}
				channels[i].chnclients.erase(channels[i].chnclients.begin() + i);
				channels[i]._clientnum--;
				if (channels[i].chnclients.size() == 0)
					channels.erase(channels.begin() + i);
			}
		}	
	}

	for (unsigned long int i = 0 ; i < pollFd.size() ; i++)
	{
		if (client.fd == pollFd[i].fd)
		{
			std::string msg = ":" + getprefix(client) + " QUIT :Leaving " + inputs[inputs.size() - 1] + "\n";
			send(client.fd, msg.c_str(), msg.length(), 0);
			close(pollFd[i].fd);
			pollFd.erase(pollFd.begin() + i);
			break;
		}
	}

	for (int i = 0; i < _srvClientNum; i++)
	{
		if (clients[i]._nickName == client._nickName){
			std::vector<Client>::iterator it;
			it = clients.begin() + i;
			std::cout << it->_nickName << '\n';
			clients.erase(clients.begin() + i);
			_srvClientNum--;
		}
	}
	return;
}

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

void Server::runCommand(Client &client)
{
	std::string msg;
	ToLower(inputs[0]);
	if (sizeof(client) < 1)
		std::cout << "hmm\n";
	// for (unsigned long int i = 0; i < inputs.size(); i++){
	// 	if (inputs[i] == "PASS"){
	// 		client.passchk = true;
	// 		if (atoi(inputs[i + 1].c_str()) != _passwd){
	// 			msg = "ERROR! Password incorrect\n";
	// 			send(client.fd, msg.c_str(), msg.length(), 0);
	// 			msg.clear();
	// 			quit(client);
	// 		}
	// 	}
	// }
	for(unsigned long int i = 0; i < inputs.size(); i++){
		if (inputs[i] == "cap")
			std::cout << "IRC cap\n";
		if (inputs[i] == "nick")
			std::cout << "IRC nick\n";
		if (inputs[i] == "join")
			std::cout << "IRC join\n";
		if (inputs[i] == "privmsg")
			std::cout << "IRC privmsg\n";
		if (inputs[i] == "quit")
			std::cout << "IRC quit\n";
		if (inputs[i] == "ping")
			std::cout << "IRC ping\n";
		if (inputs[i] == "pass")
			std::cout << "IRC pass\n";
		if (inputs[i] == "kick")
			std::cout << "IRC kick\n";
		if (inputs[i] == "user")
			std::cout << "IRC user\n";
		if (inputs[i] == "mode")
			std::cout << "IRC mode\n";
		if (inputs[i] == "invite")
			std::cout << "IRC invite\n";
		if (inputs[i] == "notice")
			std::cout << "IRC notice\n";
	}
	inputs.clear();
}