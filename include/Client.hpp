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
		bool	_nickfirst;
		bool	passchk;
	
		std::string	_nickNmae;
		std::string	_userName;
		std::string	_host;
};

#endif