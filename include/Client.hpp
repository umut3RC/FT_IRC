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

		Client &operator=( const Client &src)
		{
			fd = src.fd;
			num = src.num;
			status = src.status;
			c_pass = src.c_pass;
			_nickNamefirst = src._nickNamefirst;
			passchk = src.passchk;
			return (*this);
		}
};

#endif
