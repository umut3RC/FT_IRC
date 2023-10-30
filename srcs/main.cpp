#include "../include/Server.hpp"

int	main (int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::runtime_error("Error!\nInvalid input format! (exp: ./ircserv <port> <password>)\n");
		Server	server(argv);
		server.sstart();
	}catch(const std::exception &e){
		std::cerr << e.what();
	}catch( ... ){
		std::cerr << "Error!\nUnkown error\n";}
	return (0);
}
