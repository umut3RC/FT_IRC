#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "utils.hpp"

class Client
{
	private:
	public:
		int	fd;
		int	status;
		bool	isVerified;
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
			isVerified = src.isVerified;
			passchk = src.passchk;
			return (*this);
		}
};

#endif
