#ifndef SERVER_HPP
#define SERVER_HPP

class Server
{
	private:

	public:
		Server( void );
		~Server( void );
		Server( const Server &src );

		Server &operator=( const Server &src);

};

#endif