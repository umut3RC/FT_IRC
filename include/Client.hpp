#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "utils.hpp"

class Client
{
	private:
	public:
		int	fd;
		int	num;
		int	status;
		int	c_pass;
		bool	_nickNamefirst;
		bool	passchk;
	
		std::string	_nickName;
		std::string	_userName;
		std::string	_host;
};

#endif
