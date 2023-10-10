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
		if (!strncmp(inputs[1].c_str(), channels[i].chnName.c_str(), inputs[1].length()))
		{
			index = i;
			return (index);
		}
	}
	return (index);
}

void	Server::join_command( Client &client )
{
	commandMsg(client, "JOIN");
	int	index;
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
		if (channels[index].hasPass == 1)
		{
			if (strncmp(inputs[2].c_str(), channels[index].chnPass.c_str(), channels[index].chnPass.length())){
				std::cout << "join if pass check!1\n"; 
				msg = "ERROR! PLEASE JOIN WITH CHANNEL PASSWORD!\n";
				send(client.fd, msg.c_str(), msg.length(), 0);
				msg.clear();
				return;
			}
		}
		if (channels[index].maxUser == channels[index].chnClientsNum){
			msg = "ERROR! YOU CANNOT JOIN THIS CHANNEL USER LIMIT REACHED\n";
			execute(send(client.fd, msg.c_str(), msg.length(), 0), msg);
			return;
		}
		if (channels[index].modeP)
		{
			std::cout << "modeP == 1\n";
			if (channels[index].whiteList.empty()){
				msg = "ERROR! this is a invite only channel!\n";
				send(client.fd, msg.c_str(), msg.length(), 0);
				return;	
			}
			for (unsigned long int l = 0; l < channels[index].whiteList.size(); l++)
			{
				if (!strncmp(channels[index].whiteList[l].c_str(), client.nickName.c_str(), channels[index].whiteList[l].length()) && !channels[index].whiteList.empty()){
					channels[index].chnClients.push_back(client);
					channels[index].chnClientsNum++;
					msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
					for (int j = 0; j < channels[index].chnClientsNum; j++){
						send(channels[index].chnClients[j].fd, msg.c_str(), msg.length(), 0);
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
		channels[index].chnClients.push_back(client);
		channels[index].chnClientsNum++;
		// std::cout << "Number of client in channel: " << channels[index].chnClientsNum << std::endl;
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		for (int j = 0; j < channels[index].chnClientsNum; j++)
		{
			execute(send(channels[index].chnClients[j].fd, msg.c_str(), msg.length(), 0), "Cant send\n");
		}
		return;
	}
	else
	{
		Channel newChannel(inputs[1]);
		if (inputs.size() == 2)
			newChannel.chnPass = inputs[2];
		newChannel.chnClients.push_back(client);
		newChannel.chnClientsNum++;
		// newChannel.chnAdmin = client.nickName;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		newChannel.chnOperators.push_back(client.nickName);
		channels.push_back(newChannel);
		serverChnNum++;
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		// std::cout << "Join msg: " << msg << "\n";
		execute(send(client.fd, msg.c_str(), msg.length(), 0), "Not Sended!\n");
		msg.clear();
	}
}
