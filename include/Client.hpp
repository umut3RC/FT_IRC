#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "utils.hpp"

class Client
{
	private:
	public:
		int	fd;
		int	status;
		bool	isFirstNickAssigment;
		bool	passchk;
	
		std::string	cltPass;
		std::string	nickName;
		std::string	userName;
		std::string	host;

		Client &operator=( const Client &src)
		{
			fd = src.fd;
			status = src.status;
			cltPass = src.cltPass;
			isFirstNickAssigment = src.isFirstNickAssigment;
			passchk = src.passchk;
			return (*this);
		}
};

#endif
