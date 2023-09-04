#include "../include/Server.hpp"

Server::Server( const Server &src )
{*this = src;}

Server::~Server( void )
{
	std::cout << "Server closed. Have a good day!\n";
	close(client._clientFd);
	close(_sockfd);
}

Server::Server( char **av )
{
	std::cout << "Socket starting . . .\n";
	_port = std::atoi(av[1]);
	_passwd = std::atoi(av[2]);
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	_svclientnum = 0;
	_chnum = 0;
	if (_sockfd == -1)
		throw ("Error!\nSocket could not be created!\n");
	else
		std::cout << "Socket created successfully!\n";
}

void Server::sstart( void )
{
	signal(SIGINT, signalHandler);
	std::cout << "Socket connecting.\n";
	_sockAddr.sin_family = AF_INET;	//soket adresinin aile türünü belirtir. Burada AF_INET, IPv4 adres ailesini temsil eder. Sunucu, bu aile türünü kullanarak IPv4 adresleri ile iletişim kurar.
	_sockAddr.sin_port = htons(_port);	//sunucunun hangi port üzerinden bağlantıları dinleyeceğini belirtir. Burada htons işlevi (host to network short), 16 bitlik bir değeri ağ baytlarına (network byte order) dönüştürür. Bu nedenle 8080 portunu ağ baytlarına dönüştürerek kullanılır.
	_sockAddr.sin_addr.s_addr = INADDR_ANY;	//sunucunun hangi IP adresini dinleyeceğini belirtir. INADDR_ANY, sunucunun mevcut tüm ağ arayüzleri üzerinden gelen bağlantıları kabul edeceği anlamına gelir. Bu, sunucunun herhangi bir IP adresi ile gelen bağlantıları dinlemesini sağlar ve bu şekilde sunucunun herhangi bir ağ arabirimi veya IP adresine bağlanmasına izin verir.

	// Sunucu soketini bağlama
	if (bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr)) == -1)
	{
		throw("Error!\n Bind the server socket failed\n");
		close(client._clientFd);
		close(_sockfd);
		bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr));
	}
	listen(_sockfd, 10);
	std::cout << "Listening on port " << _port << std::endl;
	// client._clientFd = accept(_sockfd, (struct sockaddr *)&client._clientAddr, sizeof(client._clientAddr));
	client._clientFd = accept(_sockfd, NULL, NULL);
	if (client._clientFd == -1)
		throw ("Error!\nAccepting client connection.\n");
	// İstemciden gelen veriyi okuma ve ekrana yazdırma
	while (1)
	{
		std::vector<std::string> clientMsgSplit;
		std::vector<std::string>::iterator clientMsgSplit_iter;
		recv(client._clientFd, buffer, sizeof(buffer), 0);
		// std::cout << "From client: " << buffer << std::endl;
		// std::cout << ">>****>" << buffer << "<****<<";

		clientMsgSplit = splitString(buffer, '\n');
		clientMsgSplit_iter = clientMsgSplit.begin();
		while (clientMsgSplit_iter != clientMsgSplit.end())
		{
			// std::cout << ">>**>>" << *clientMsgSplit_iter << "<<**<<\n";
			checkServerCommands(*clientMsgSplit_iter);
			++clientMsgSplit_iter;
		}
		// İstemciye yanıt gönderme
		// const char *response = "Hello from server!";
		// send(client._clientFd, response, strlen(response), 0);
	}
	// Soketleri kapatma
	close(client._clientFd);
	close(_sockfd);
}

Server &Server::operator=( const Server &src)
{
	this->_port = src._port;
	this->_passwd = src._passwd;
	this->_sockfd = src._sockfd;
	this->_svclientnum = src._svclientnum;
	this->_chnum = src._chnum;
	return (*this);
}
