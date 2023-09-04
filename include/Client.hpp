#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "utils.hpp"

class Client
{
	public:
		int	_port;
		int	_passwd;
		int	_clientFd;
		int	_clientAddr;
		int	_svclientnum;
		int	_chnum;
		char	buffer[1024];
};

#endif