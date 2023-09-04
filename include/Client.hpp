#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "utils.hpp"

class Client
{
	public:

		int	_passwd;
		int	_clientFd;
		int	_clientAddr;
		char	buffer[1024];
};

#endif