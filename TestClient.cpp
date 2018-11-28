#include "pch.h"
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <windows.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;


void main()
{
	std::string ipAddress = "192.168.1.58"; //Ton adresse IP
	int port = 54888; //Le port ne change pas

	WSADATA data;
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &data);

	if (wsok != 0)
	{
		std::cout << "Erreur WSAStratup " << wsok << std::endl;
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		std::cout << "Erreur socket " << std::endl;
		return;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	connect(sock, (sockaddr*)&hint, sizeof(hint));


	while (1)
	{
		char buffer[4096];
		int i = 0;
		send(sock, "salut", 10, 0);

		Sleep(2500);

		i = recv(sock, buffer, sizeof(buffer), 0);


		std::cout << string(buffer, 0,i) << std::endl;

		Sleep(2500);
	}


	closesocket(sock);
	WSACleanup();


}
