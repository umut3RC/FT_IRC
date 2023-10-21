#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream> //cout, cin, cerr
#include <sys/socket.h> // socket, setsockopt, getsockname, bind, connect, listen, accept, send, recv
#include <unistd.h> // close
#include <netdb.h> // getprotobyname, gethostbyname, freeaddrinfo, getaddrinfo
#include <arpa/inet.h> // htonl, htons, ntohs, ntohl, inet_addr, inet_ntoa,
#include <signal.h> // signal
#include <fcntl.h> // lseek, fstat, fcntl
#include <poll.h> // poll
#include <netinet/in.h> // struct sockaddr_in
#include <vector>
#include <map>
#include <functional>
#include <algorithm> // std::transform
#include <cctype>	// std::toupper
#include <string>
#include <cstring>
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"


#define ERR_UNKNOWNCOMMAND(source, command)				"421 " + source + " " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(source, command)				"461 " + source + " " + command + " :Not enough parameters"
// #define ERR_NEEDMOREPARAMS(prefix, command)				"461 " + prefix + " " +  command + " :Not enough parameters"
#define ERR_NOTREGISTERED(source)						"451 " + source + " :You have not registered"
#define ERR_ALREADYREGISTERED(source)					"462 " + source + " :You may not reregister"
#define ERRserverPassMISMATCH(source)						"464 " + source + " :Password incorrect"
#define ERR_NONICKNAMEGIVEN(nickname)					"431 " + nickname + " :Nickname not given"
#define ERRnickNameINUSE(nickname)						"433 " + nickname + " " + nickname + " :Nickname is already in use"
#define ERR_TOOMANYCHANNELS(source, channel)			"405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(source, channel)				"442 " + source + " " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(source, channel)				"403 " + source + " " + channel + " :No such channel"
#define ERR_BADCHANNELKEY(source, channel)				"475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_NOSUCHNICK(source, nickname)				"401 " + source + " " + nickname + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(source, nickname, channel)	"441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"
#define ERR_CHANOPRIVSNEEDED(source, channel)			"482 " + source + " " + channel + " :You're not channel operator\r\n"
#define ERR_CHANNELISFULL(source, channel)				"471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_CANNOTSENDTOCHAN(source, channel)			"404 " + source + " " + channel + " :Cannot send to channel"
#define ERR_ERRONEUSNICKNAME(source, nick)				"432 " + source + " " + nick + " :Erroneous nickname"
#define ERR_UMODEUNKNOWNFLAG(source, nick)				"501 " + source + " " + nick + " :Unknown MODE flag"
#define ERR_USERSDONTMATCH(source)						"502 " + source + " :Cannot change mode for other users"
#define ERR_INVITEONLYCHAN(source)						"473 " + source + " :Cannot join channel (+i)"

// NUMERIC REPLIES
#define RPL_WELCOME(source, server)															"001 " + source + " :" + "Welcome " + source + " to the " + server + " server!\r\n"
#define RPL_NAMREPLY(source, channel, users)												"353 " + source + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(source, channel)														"366 " + source + " " + channel + " :End of /NAMES list."
#define RPL_WHOISUSER(source, nickname, username, hostname, port, realname)					"311 " + source + " " + nickname + " ~" + username + " " + hostname + ":" + port + " * :" + realname
#define RPL_WHOISSERVER(source, server)														"312 " + source + " * :" + server
#define RPL_WHOISCHANNELS(source, nickname, channels)										"319 " + source + " " + nickname + " :" + channels 
#define RPL_ENDOFWHOIS(source, nickname)													"318 " + source + " " + nickname + " :End of /WHOIS list"
#define RPL_TOPIC(source, channel, topic)													"332 " + source + " " + channel + " :" + topic
#define RPL_WHOREPLY(source, channel, user, host, server, nick, flag, hopcount, realname)	"352 " + source + " " + channel + " " + user + " " + host + " " + server + " " + nick + " H" + flag + " :" + hopcount  + " " + realname
#define RPL_ENDOFWHO(source, channel)														"315 " + source + " " + channel + " :End of WHO list"
#define RPL_LISTSTART(client)																"321 " + client + " Channel - Users Count - Channel Topic"
#define RPL_LIST(client, channel, clientCount, topic)										"322 " + client + " " + channel + " - " + clientCount + " - :" + topic 
#define RPL_LISTEND(client)																	"323 " + client + " :End of /LIST"
#define RPL_INFO(client, string)															"371 " + client + " :" + string
#define RPL_ENDOFINFO(client)																"374 " + client + " :End of INFO list"
#define ERR_PASSWDMISMATCH(client)															"464 " + client + " :Password incorrect"
//410 CAP END bilgini tekrardan istiyor.

// COMMAND REPLIES
#define RPL_JOIN(source, channel)						":" + source + " JOIN :" + channel
#define RPL_PART(source, channel)					":" + source + " PART :" + channel// :" + message
#define RPL_PING(source, token)							":" + source + " PONG :" + token
#define RPL_PONG(source, token)							":" + source + " PING :" + token
#define RPL_PRIVMSG(source, target, message)			":" + source + " PRIVMSG " + target + " " + message // :" + message
#define RPL_NOTICE(source, target, message)				":" + source + " NOTICE " + target + " :" + message
#define RPL_QUIT(source, message)						":" + source + " QUIT :Quit: " + message
#define RPL_KICK(source, channel, target, reason)		":" + source + " KICK " + channel + " " + target + " " + reason // :" + reason
#define RPL_MODE(source, channel, modes, args)			":" + source + " MODE " + channel + " " + modes + " " + args
#define RPL_NICK(source, nickname)						":" + source + " NICK " + nickname
#define ERROR(source, message)							":" + source + " ERROR " + " :" + message

std::vector<std::string> splitString(const std::string& input, char delimiter);
void	ToLower(std::string &s);
void	ToUpper(std::string &s);
void	signalHandler( int s );
void	execute(int ret, std::string err, int ERR_MSG);

#endif