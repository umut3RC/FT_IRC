//https://stackoverflow.com/questions/43399621/join-command-for-irc-protocol
/*
Response 1: :<UserJID> JOIN :<ChannelName>
Response 2: :<Domain> <[RPL_TOPIC][1]> <NickName> <ChannelName> :<Topic>
Response 3:
:<Domain> <[RPL_NAMREPLY][1]> <NickName> = <ChannelName> : <NameList>
:<Domain> <[RPL_ENDOFNAMES][1]> <NickName> <ChannelName> :End of Names list
*/
#include "../../include/Server.hpp"

/*
Join komutu, bir istemcinin bir kanala katılmak istediğini belirten bir komuttur. Bu komutun formatı şu şekildedir:

/join #kanal_ismi
Kanal ismi, istemcinin katılmak istediği kanalın adıdır. Kanal ismi, # işaretiyle başlamalıdır.

İstemciden gelen Join komutunu yakaladıktan sonra, aşağıdaki adımları uygulamanız gerekir:

1.Kanalın var olup olmadığını kontrol edin. Kanal yoksa, oluşturun.
2.Kanalın zaten dolu olup olmadığını kontrol edin. Kanal doluysa, istemciyi kanala eklemeyin.
3.İstemciyi kanala ekleyin. Bu, kanalın kullanıcı listesine istemcinin takma adını eklemeyi içerir.
4.Kanala tüm kullanıcılara katılış bildirimi gönderin. Bu, kanalda bulunan tüm kullanıcılara, istemcinin kanala katıldığını bildiren bir mesaj göndermeyi içerir.

*/
int	Server::findChannel( void )
{
	int	index = -1;
	for (int i = 0 ; i < (int)channels.size(); i++)
	{
		if (!strncmp(inputs[1].c_str(), channels[i]._chname.c_str(), inputs[1].length()))
		{
			index = i;
			return (index);
		}
	}
	return (index);
}

// void	Server::join_command( Client &client )
// {
// 	std::string msg = getprefix(client);

// 	// std::cout << "IRC: Called JOIN command\n";
// 	// const char* join_command = "JOIN #a 1234 #a\r\n"; // Örnek bir oda adı
// 	// try
// 	// {
// 	// 	send(client.fd, join_command, strlen(join_command), 0);
// 	// }
// 	// catch(const std::exception& e)
// 	// {
// 	// 	std::cerr << e.what() << '\n';
// 	// }
// 	// std::cout << inputs.size() << "IiIIIHIHIHIHIHIHIHI\n";
// 	if (inputs.size() > 3)
// 	{
// 		throw std::runtime_error("Error!\nInvalid JOIN syntax!\nUSE:/join <channel> <channel passwd>\n");
// 		msg = "join args must be like this /join <channel> <channel passwd>\n";
// 		if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 		{
// 			msg.clear();
// 			throw std::runtime_error("Error!\nDidn't sended!\n");
// 		}
// 	}
// 	if (inputs[1][0] != '#')
// 		inputs[1] = '#' + inputs[1];
// 	for (unsigned long int i = 0; i < channels.size(); i++)
// 	{
// 		if (!strncmp(inputs[1].c_str(), channels[i]._chname.c_str(), inputs[1].length()))
// 		{
// 			std::cout << "found?";
// 			if (channels[i].passprotected == 1){
// 				if (strncmp(inputs[2].c_str(), channels[i]._chpasswd.c_str(), channels[i]._chpasswd.length()))
// 				{
// 					std::cout << "join if pass check!1\n"; 
// 					msg = "ERROR! PLEASE JOIN WITH CHANNEL PASSWORD!\n";
// 					execute(send(client.fd, msg.c_str(), msg.length(), 0), "Error!\nDidn't sended!\n");
// 					msg.clear();
// 					// if ( < 0)
// 					// {
// 					// 	msg.clear();
// 					// 	throw std::runtime_error("Error!\nDidn't sended!\n");
// 					// }
// 				}
// 			}
// 			if (channels[i].maxUser == channels[i]._clientnum)
// 			{
// 				msg = "ERROR! YOU CANNOT JOIN THIS CHANNEL USER LIMIT REACHED\n";
// 				if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 				{
// 					msg.clear();
// 					throw std::runtime_error("Error!\nDidn't sended!\n");
// 				}
// 			}
// 			if (channels[i].ifp == 1){
// 				std::cout << "ifp == 1\n";
// 				if (channels[i]._whitelist.empty()){
// 					msg = "ERROR! this is a invite only channel!\n";
// 					if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 					{
// 						msg.clear();
// 						throw std::runtime_error("Error!\nDidn't sended!\n");
// 					}
// 				}
// 				for (unsigned long int l = 0; l < channels[i]._whitelist.size(); l++)
// 				{
// 					if (!strncmp(channels[i]._whitelist[l].c_str(), client._nickName.c_str(), channels[i]._whitelist[l].length()) && !channels[i]._whitelist.empty()){
// 						channels[i].chnclients.push_back(client);
// 						channels[i]._clientnum++;
// 						msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 						for (int j = 0; j < channels[i]._clientnum; j++){
// 							if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 							{
// 								throw std::runtime_error("Error!\nDidn't sended!\n");
// 							}
// 						}
// 						msg.clear();
// 						return;
// 					}
// 					else{
// 						msg = "ERROR! this is a invite only channel!\n";
// 						if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 						{
// 							msg.clear();
// 							throw std::runtime_error("Error!\nDidn't sended!\n");
// 						}
// 					}
// 				}
// 			}
// 			channels[i].chnclients.push_back(client);
// 			channels[i]._clientnum++;
// 			std::cout << "CLNUM:" << channels[i]._clientnum << std::endl;
// 			msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 			for (int j = 0; j < channels[i]._clientnum; j++){
// 				if (send(channels[i].chnclients[j].fd, msg.c_str(), msg.length(), 0) < 0)
// 					throw std::runtime_error("Error!\nDidn't sended!\n");
// 			}
// 			return;
// 		}
// 	}
// 	Channel newCh(inputs[1]);
// 	if (inputs.size() == 2)
// 		newCh._chpasswd = inputs[2];
// 	newCh._chname = inputs[1];
// 	newCh.chnclients.push_back(client);
// 	newCh._clientnum++;
// 	newCh._admin = client._nickName;
// 	channels.push_back(newCh);
// 	_chNum++;
// 	msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 	std::cout << "MSG->>>>>" << msg << "\n";
// 	send(client.fd, msg.c_str(), msg.length(), 0);
// 	msg.clear();
// }
//-----------------------------------------------------------
// void	Server::join_command( Client &client )
// {
// 	std::string	msg;

// 	if (token.size() < 2)//az arguman
// 	{
// 		_clients[fd]->clientMsgSender(fd, ERR_NEEDMOREPARAMS(_clients[fd]->getNickName(), "PASS")); return ; }

// 	token[1] = (token[1][0] != '#' ? "#" + token[1] : token[1]);
// 	for (size_t i = 0 ; i < _clients[fd]->_channels.size() ; i++) //aradığı kanal içinde kendisi varmı
// 	{
// 		if (_clients[fd]->_channels[i]->getName() == token[1]) {
// 			msg = "You're already on this channel!"; ft_write(fd, msg); return ; } }

// 	if (_channels.find(token[1]) == _channels.end())//kanal bulunamazsa oluştur
// 	{
// 		msg = token[1] + " creating channel..."; ft_write(fd, msg);
// 		msg = "Admin login"; ft_write(fd, msg);
// 		_channels[token[1]] = new Channel(_clients[fd], token[1], token.size() > 2 ? token[2] : "");
// 		_clients[fd]->_channels.push_back(_channels[token[1]]);
// 		_clients[fd]->casting(fd, _channels[token[1]]->_channelClients, RPL_JOIN(_clients[fd]->getPrefixName(), token[1]) + " :" + _clients[fd]->getNickName());
// 		return ;//                                                     ":" + source + " JOIN :" + channel                                                       	
// 	}
	
// 	if (_channels[token[1]]->getClientCount() >= _channels[token[1]]->getMaxClientCount()) {
// 		msg = "Channel is full!"; ft_write(fd, msg); }
// 	else if (!(_channels[token[1]]->getPassword().empty()) && _channels[token[1]]->getPassword() != token[2]) {
// 		msg = "Failed, password error!"; ft_write(fd, msg); }
// 	else
// 	{
// 		_channels[token[1]]->_channelClients.push_back(_clients[fd]);
// 		_clients[fd]->_channels.push_back(_channels[token[1]]);
// 		_channels[token[1]]->setClientCount(_channels[token[1]]->getClientCount() + 1);
// 		_clients[fd]->casting(fd, _channels[token[1]]->_channelClients, RPL_JOIN(_clients[fd]->getPrefixName(), token[1]) + " :" + _clients[fd]->getNickName());
// 	}
// }
//------------------------------------------------------------------------

//----------------------------------------_V_simple_working_V_-------------------
void	Server::join_command( Client &client )
{
	std::cout << "Client wanna join->" << client._nickName << "\n" << client._userName << "\n";
	int	index;
	// std::string joinMessage = "JOIN #a uercan";
	// send (client.fd, joinMessage.c_str(), joinMessage.length(), 0);
	// std::cout << "JOIN FONKSIYONU" << '\n';
	std::string msg = getprefix(client);
	if (inputs.size() > 3){
		std::cerr << "join ARG Error!" << std::endl;
		msg = "join args must be like this /join <channel> <channel passwd>\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "not Sended\n");
		msg.clear();
		return;
	}
	if (inputs[1][0] != '#')
		inputs[1] = '#' + inputs[1];
	index = findChannel();
	if (index > -1)
	{
		if (channels[index].passprotected == 1)
		{
			if (strncmp(inputs[2].c_str(), channels[index]._chpasswd.c_str(), channels[index]._chpasswd.length())){
				std::cout << "join if pass check!1\n"; 
				msg = "ERROR! PLEASE JOIN WITH CHANNEL PASSWORD!\n";
				send(client.fd, msg.c_str(), msg.length(), 0);
				msg.clear();
				return;
			}
		}
		if (channels[index].maxUser == channels[index]._clientnum){
			msg = "ERROR! YOU CANNOT JOIN THIS CHANNEL USER LIMIT REACHED\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), msg);
			return;
		}
		if (channels[index].ifp)
		{
			std::cout << "ifp == 1\n";
			if (channels[index]._whitelist.empty()){
				msg = "ERROR! this is a invite only channel!\n";
				send(client.fd, msg.c_str(), msg.length(), 0);
				return;	
			}
			for (unsigned long int l = 0; l < channels[index]._whitelist.size(); l++)
			{
				if (!strncmp(channels[index]._whitelist[l].c_str(), client._nickName.c_str(), channels[index]._whitelist[l].length()) && !channels[index]._whitelist.empty()){
					channels[index].chnclients.push_back(client);
					channels[index]._clientnum++;
					msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
					for (int j = 0; j < channels[index]._clientnum; j++){
						send(channels[index].chnclients[j].fd, msg.c_str(), msg.length(), 0);
					}
					msg.clear();
					return;
				}
				else{
					msg = "ERROR! this is a invite only channel!\n";
					send(client.fd, msg.c_str(), msg.length(), 0);
					return;
				}
			}
		}
		channels[index].chnclients.push_back(client);
		channels[index]._clientnum++;
		std::cout << "Number of client in channel: " << channels[index]._clientnum << std::endl;
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		for (int j = 0; j < channels[index]._clientnum; j++)
		{
			execute(send(channels[index].chnclients[j].fd, msg.c_str(), msg.length(), 0), "Cant send\n");
		}
		return;
	}
	else
	{
		Channel newChannel(inputs[1]);
		if (inputs.size() == 2)
			newChannel._chpasswd = inputs[2];
		newChannel.chnclients.push_back(client);
		newChannel._clientnum++;
		newChannel._admin = client._nickName;
		channels.push_back(newChannel);
		_chNum++;
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		std::cout << "Join msg: " << msg << "\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Not Sended!\n");
		msg.clear();
	}
}

//-------------------------------------------------------------------------------------------------------------------------LASTA
// void	Server::join_command( Client &client )
// {
// 	std::cout << "IRC: Called JOIN command\n";
// 	std::string msg = getprefix(client);

// 	if (inputs.size() > 3)
// 	{
// 		throw std::runtime_error("Error!\nInvalid JOIN syntax!\nUSE:/join <channel> <channel passwd>\n");
// 		msg = "join args must be like this /join <channel> <channel passwd>\n";
// 		if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 		{
// 			msg.clear();
// 			throw std::runtime_error("Error!\nDidn't sended!\n");
// 		}
// 	}
// 	if (inputs[1][0] != '#')
// 		inputs[1] = '#' + inputs[1];
// 	for (unsigned long int i = 0; i < channels.size(); i++)
// 	{
// 		if (!strncmp(inputs[1].c_str(), channels[i]._chname.c_str(), inputs[1].length()))
// 		{
// 			std::cout << "found?";
// 			if (channels[i].passprotected == 1){
// 				if (strncmp(inputs[2].c_str(), channels[i]._chpasswd.c_str(), channels[i]._chpasswd.length()))
// 				{
// 					std::cout << "join if pass check!1\n"; 
// 					msg = "ERROR! PLEASE JOIN WITH CHANNEL PASSWORD!\n";
// 					execute(send(client.fd, msg.c_str(), msg.length(), 0), "Error!\nDidn't sended!\n");
// 					msg.clear();
// 					// if ( < 0)
// 					// {
// 					// 	msg.clear();
// 					// 	throw std::runtime_error("Error!\nDidn't sended!\n");
// 					// }
// 				}
// 			}
// 			if (channels[i].maxUser == channels[i]._clientnum)
// 			{
// 				msg = "ERROR! YOU CANNOT JOIN THIS CHANNEL USER LIMIT REACHED\n";
// 				if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 				{
// 					msg.clear();
// 					throw std::runtime_error("Error!\nDidn't sended!\n");
// 				}
// 			}
// 			if (channels[i].ifp == 1){
// 				std::cout << "ifp == 1\n";
// 				if (channels[i]._whitelist.empty()){
// 					msg = "ERROR! this is a invite only channel!\n";
// 					if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 					{
// 						msg.clear();
// 						throw std::runtime_error("Error!\nDidn't sended!\n");
// 					}
// 				}
// 				for (unsigned long int l = 0; l < channels[i]._whitelist.size(); l++)
// 				{
// 					if (!strncmp(channels[i]._whitelist[l].c_str(), client._nickName.c_str(), channels[i]._whitelist[l].length()) && !channels[i]._whitelist.empty()){
// 						channels[i].chnclients.push_back(client);
// 						channels[i]._clientnum++;
// 						msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 						for (int j = 0; j < channels[i]._clientnum; j++){
// 							if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 							{
// 								throw std::runtime_error("Error!\nDidn't sended!\n");
// 							}
// 						}
// 						msg.clear();
// 						return;
// 					}
// 					else{
// 						msg = "ERROR! this is a invite only channel!\n";
// 						if (send(client.fd, msg.c_str(), msg.length(), 0) < 0)
// 						{
// 							msg.clear();
// 							throw std::runtime_error("Error!\nDidn't sended!\n");
// 						}
// 					}
// 				}
// 			}
// 			channels[i].chnclients.push_back(client);
// 			channels[i]._clientnum++;
// 			std::cout << "CLNUM:" << channels[i]._clientnum << std::endl;
// 			msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 			for (int j = 0; j < channels[i]._clientnum; j++){
// 				if (send(channels[i].chnclients[j].fd, msg.c_str(), msg.length(), 0) < 0)
// 					throw std::runtime_error("Error!\nDidn't sended!\n");
// 			}
// 			return;
// 		}
// 	}
// 	Channel newCh(inputs[1]);
// 	if (inputs.size() == 2)
// 		newCh._chpasswd = inputs[2];
// 	newCh._chname = inputs[1];
// 	newCh.chnclients.push_back(client);
// 	newCh._clientnum++;
// 	newCh._admin = client._nickName;
// 	channels.push_back(newCh);
// 	_chNum++;
// 	msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 	std::cout << "MSG->>>>>" << msg << "\n";
// 	send(client.fd, msg.c_str(), msg.length(), 0);
// 	msg.clear();
// }