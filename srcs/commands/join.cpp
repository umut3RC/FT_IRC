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
void	Server::join_command( Client &client )
{
	std::string chn = getprefix(client);

	std::cout << "IRC: JOIN command\n";
	if (inputs.size() > 3)
	{
		throw std::runtime_error("Error!\nInvalid JOIN syntax!\nUSE:/join <channel> <channel passwd>\n");
		chn = "join args must be like this /join <channel> <channel passwd>\n";
		if (send(client.fd, chn.c_str(), chn.length(), 0) < 0)
		{
			chn.clear();
			throw std::runtime_error("Error!\nDidn't sended!\n");
		}
	}
	if (inputs[1][0] != '#')
		inputs[1] = '#' + inputs[1];
	for (unsigned long int i = 0; i < channels.size(); i++)
	{
		if (!strncmp(inputs[1].c_str(), channels[i]._chname.c_str(), inputs[1].length()))
		{
			if (channels[i].passprotected == 1){
				if (strncmp(inputs[2].c_str(), channels[i]._chpasswd.c_str(), channels[i]._chpasswd.length()))
				{
					std::cout << "join if pass check!1\n"; 
					chn = "ERROR! PLEASE JOIN WITH CHANNEL PASSWORD!\n";
					if (send(client.fd, chn.c_str(), chn.length(), 0) < 0)
					{
						chn.clear();
						throw std::runtime_error("Error!\nDidn't sended!\n");
					}
				}
			}
			if (channels[i].chmaxuser == channels[i]._clientnum)
			{
				chn = "ERROR! YOU CANNOT JOIN THIS CHANNEL USER LIMIT REACHED\n";
				if (send(client.fd, chn.c_str(), chn.length(), 0) < 0)
				{
					chn.clear();
					throw std::runtime_error("Error!\nDidn't sended!\n");
				}
			}
			if (channels[i].ifp == 1){
				std::cout << "ifp == 1\n";
				if (channels[i]._whitelist.empty()){
					chn = "ERROR! this is a invite only channel!\n";
					if (send(client.fd, chn.c_str(), chn.length(), 0) < 0)
					{
						chn.clear();
						throw std::runtime_error("Error!\nDidn't sended!\n");
					}
				}
				for (unsigned long int l = 0; l < channels[i]._whitelist.size(); l++)
				{
					if (!strncmp(channels[i]._whitelist[l].c_str(), client._nickName.c_str(), channels[i]._whitelist[l].length()) && !channels[i]._whitelist.empty()){
						channels[i].chnclients.push_back(client);
						channels[i]._clientnum++;
						chn += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
						for (int j = 0; j < channels[i]._clientnum; j++){
							if (send(client.fd, chn.c_str(), chn.length(), 0) < 0)
							{
								throw std::runtime_error("Error!\nDidn't sended!\n");
							}
						}
						chn.clear();
						return;
					}
					else{
						chn = "ERROR! this is a invite only channel!\n";
						if (send(client.fd, chn.c_str(), chn.length(), 0) < 0)
						{
							chn.clear();
							throw std::runtime_error("Error!\nDidn't sended!\n");
						}
					}
				}
			}
			channels[i].chnclients.push_back(client);
			channels[i]._clientnum++;
			std::cout << "CLNUM:" << channels[i]._clientnum << std::endl;
			chn += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
			for (int j = 0; j < channels[i]._clientnum; j++){
				if (send(channels[i].chnclients[j].fd, chn.c_str(), chn.length(), 0) < 0)
					throw std::runtime_error("Error!\nDidn't sended!\n");
			}
			return;
		}
	}
}
