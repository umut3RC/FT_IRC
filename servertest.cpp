#include <iostream> //cout, cin, cerr
#include <sys/socket.h> // socket, setsockopt, getsockname, bind, connect, listen, accept, send, recv
#include <unistd.h> // close
#include <netdb.h> // getprotobyname, gethostbyname, freeaddrinfo, getaddrinfo
#include <arpa/inet.h> // htonl, htons, ntohs, ntohl, inet_addr, inet_ntoa,
#include <signal.h> // signal
#include <fcntl.h> // lseek, fstat, fcntl
#include <poll.h> // poll
#include <netinet/in.h> // struct sockaddr_in
#include <vector>
#include <map>
#include <functional>
#include <algorithm> // std::transform
#include <cctype>	// std::toupper
#include <string>
#include <cstring>

int main()
{
	int socfd = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in saddr, clientAddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6667);
	saddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(socfd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
	{
		std::cerr << "Error binding server socket." << std::endl;
		return 1;
	}
	listen(socfd, 10);
	int cfd;
	socklen_t clientAddrSize = sizeof(clientAddr);
	char buffer[1024];
	cfd = accept(socfd, (struct sockaddr *)&clientAddr, &clientAddrSize);
	std::string msg = "MERHABA!\n";
	send(cfd, msg.c_str(), sizeof(msg), 0);
	while (1)
	{
		recv(cfd, buffer, sizeof(buffer), 0);
		std::cout << buffer << "\n";
		if (!strcmp(buffer, "JOIN"))
		{
			std::string msg = ":JOIN #oda nick@host 1234\n";
			send(cfd, msg.c_str(), sizeof(msg), 0);
		}
	}
	return (0);
}