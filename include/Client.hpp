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
		bool	nickNamefirst;
		bool	passchk;
	
		std::string	nickName;
		std::string	userName;
		std::string	host;

		Client &operator=( const Client &src)
		{
			fd = src.fd;
			num = src.num;
			status = src.status;
			c_pass = src.c_pass;
			nickNamefirst = src.nickNamefirst;
			passchk = src.passchk;
			return (*this);
		}
};

#endif
