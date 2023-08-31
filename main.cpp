#include "Server.hpp"

int	main (int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw ("Invalid input format! (exp: ./ircserv <port> <password>)\n");
		Server	server;
		server.;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	catch(const std::string& e)
	{
		std::cerr << e << '\n';
		return (2);
	}
	return (0);
}