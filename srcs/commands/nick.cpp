#include "../../include/Server.hpp"

void	Server::nick_command( Client &client )
{
	std::cout << "IRC: Called NICK command\n";
	// for (int i = 0; i < (int)inputs.size(); i++)
	// {
	// 	std::cout << "Nick: " << i << ": " << inputs[i] << "\n";
	// }
	try
	{
		client._nickName = inputs.at(1);
		client._userName = inputs.at(2);
		client._host = inputs.at(5);
		std::string msg = ": NICK " + client._nickName + "@" + client._host;
		execute(send(client.fd, msg.c_str(), sizeof(msg), 0), "ERR");
		msg = "Nick name changed.";
		// std::cout << "New Client: " << client._nickName << " " << client._userName << "\n";
		execute(send(client.fd, msg.c_str(), sizeof(msg), 0), "ERR");
	}
	catch(const std::out_of_range &e)
	{
		execute(send(client.fd, "out_of_range", strlen("out_of_range"), 0), "out_of_range");
		//"461 " + prefix + " " +  command + " :Not enough parameters"
	}
}


// std::string msg;
// /*working*/
// void	Server::nick_command( Client &client )
// {
// 	std::cout << "NICK FUNC" << '\n';
// 	int nindex = 0;
// 	if (client.passchk == false){
// 		std::cout << "ft_ex" << '\n';
// 		msg = "ERROR! passcheck failed!\n";
// 		send(client.fd, msg.c_str(), strlen(msg.c_str()), 0);
// 		msg.clear();
// 		quit_command(client);
// 	}
// 	if (_srvClientNum == 1 && client.passchk == false)
// 		return;
// 	if (!client._nickNamefirst)
// 	{
// 		unsigned long int i = 0;
// 		while (i < inputs.size())
// 		{
// 			if (inputs[i] == "NICK"){
// 				nindex = i + 1;
// 				//ilk defa nick alan icin ayni nick kontrolu
// 				for (unsigned long int j = 0; j < clients.size(); j++){
// 					if (inputs[nindex] == clients[j]._nickName){
// 						std::cout << "nick in use" << '\n';
// 							quit_command(client);
// 					}
// 				}
// 				client._nickName = inputs[i + 1];
// 			}
// 			if (inputs[i] == "USER")
// 				client._userName = inputs[i + 1];
// 			else if (inputs[i][0] == ':')
// 				client._host = inputs[i - 1];
// 			i++;
// 		}
// 		//ikinci nick komutunda yeniden buraya gelmesin diye
// 		client._nickNamefirst = true;
// 	}
// 	else
// 	{
// 		//ayni nick kontrolu
// 		for (unsigned long int i = 0; i < clients.size(); i++){
// 			std::cout << "SPINN" << '\n';
// 			if (!strncmp(inputs[1].c_str(), clients[i]._nickName.c_str(), strlen(inputs[1].c_str()))){
// 				std::cout << "nick in use" << '\n';
// 				msg = "ERROR! nick in use!\n";
// 				send(client.fd, msg.c_str(), msg.length(), 0);
// 				msg.clear();
// 				if (!client._nickName.empty())
// 					return;
// 				else
// 					quit_command(client);
// 			}
// 		}
// 		// var olan kisinin nickinin degistigi kisim
// 		std::cout << "nickfunc." << client._nickName << '\n';
// 		std::string newnick = ':' + client._nickName;
// 		newnick = getprefix(client);
// 		newnick += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
// 		send(client.fd, newnick.c_str(), newnick.length(), 0);
// 		for (unsigned long int k = 0; k < channels.size(); k++)
// 		{
// 			if (client._nickName == channels[k]._admin)
// 			{
// 				std::cout << "ADMIN degisti" << '\n';
// 				channels[k]._admin = inputs[1];
// 			}
// 		}
// 		client._nickName = inputs[1];
// 	}
// }
