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
	std::cout << "/--------------------------\\\n";
	std::cout << "|   IRC: Socket starting   |\n";
	std::cout << "\\--------------------------/\n";
	_port = std::atoi(av[1]);
	_passwd = std::atoi(av[2]);
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	_srvClientNum = 0;
	_chNum = 0;
	setCommands();
	if (_sockfd == -1)
		throw std::runtime_error("Error!\nSocket could not be created!\n");
	else
		std::cout << "IRC: Socket created successfully!\n";

	// SILINECEK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)=/)&!'+!'^
	int val = 1;
	setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

void	Server::sstart( void )
{
	signal(SIGINT, signalHandler);
	std::cout << "IRC: Socket connecting.\n";
	_sockAddr.sin_family = AF_INET;	//soket adresinin aile türünü belirtir. Burada AF_INET, IPv4 adres ailesini temsil eder. Sunucu, bu aile türünü kullanarak IPv4 adresleri ile iletişim kurar.
	_sockAddr.sin_port = htons(_port);	//sunucunun hangi port üzerinden bağlantıları dinleyeceğini belirtir. Burada htons işlevi (host to network short), 16 bitlik bir değeri ağ baytlarına (network byte order) dönüştürür. Bu nedenle 8080 portunu ağ baytlarına dönüştürerek kullanılır.
	_sockAddr.sin_addr.s_addr = INADDR_ANY;	//sunucunun hangi IP adresini dinleyeceğini belirtir. INADDR_ANY, sunucunun mevcut tüm ağ arayüzleri üzerinden gelen bağlantıları kabul edeceği anlamına gelir. Bu, sunucunun herhangi bir IP adresi ile gelen bağlantıları dinlemesini sağlar ve bu şekilde sunucunun herhangi bir ağ arabirimi veya IP adresine bağlanmasına izin verir.

	// Sunucu soketini bağlama
	execute(bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr)), "Error!\nBind the server socket failed\n");
	// if (bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr)) == -1)
	// {
	// 	throw std::runtime_error("Error!\nBind the server socket failed\n");
	// 	// close(client._clientFd);
	// 	// close(_sockfd);
	// 	// bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr));
	// }
	execute(listen(_sockfd, 10), "Error!\nListening failed\n");
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
				quit_command(clients[i - 1]);
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
					std::cout << "IRC: New client connected.\n";
					_srvClientNum++;
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
						clients[i - 1].num = i - 1;
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


