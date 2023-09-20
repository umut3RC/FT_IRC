#include "../../include/Server.hpp"

void	Server::ping_command(Client &client)
{
	std::cout << "IRC: Called PING command\n";
	char buffer[1024];
	ssize_t bytesRead;

	// İstemciden gelen veriyi okuyun
	bytesRead = recv(client.fd, buffer, sizeof(buffer), 0);

	if (bytesRead > 0)
	{
		buffer[bytesRead] = '\0'; // Verinin sonunu işaretleyin
		std::string message(buffer);

		// PING komutunu işleme
		if (message.substr(0, 4) == "PING") {
			std::string pingData = message.substr(5); // PING komutunun verisini alın
			std::string pongResponse = "PONG " + pingData + "\r\n";
			send(client.fd, pongResponse.c_str(), pongResponse.size(), 0);
		}
	}
}