#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "utils.hpp"

class Client
{
	private:
	public:
		int	fd;
		int	status;
		int	c_pass;
		bool	isFirstNickAssigment;
		bool	passchk;
	
		std::string	nickName;
		std::string	userName;
		std::string	host;

		Client &operator=( const Client &src)
		{
			fd = src.fd;
			status = src.status;
			c_pass = src.c_pass;
			isFirstNickAssigment = src.isFirstNickAssigment;
			passchk = src.passchk;
			return (*this);
		}
};

#endif
