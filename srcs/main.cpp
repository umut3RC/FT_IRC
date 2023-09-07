#include "../include/Server.hpp"

int	main (int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::runtime_error("Error!\nInvalid input format! (exp: ./ircserv <port> <password>)\n");
		Server	server(argv);// <-- soket oluşturuldu;
		server.sstart();
	}catch(const std::exception& e){
		std::cerr << e.what();
	}catch(const char *e){
		std::cerr << e;
	}catch( ... ){
		std::cerr << "Error! Unkown error" << '\n';
	}
	return (0);
}
