#include <iostream>
#include <cstdint>
#include <winsock2.h>//windows.
#include <WS2tcpip.h>
#include <thread>
#include <chrono>
#include <memory>

//http://wisdom.sakura.ne.jp/system/winapi/winsock/winSock5.html

//this is gabage code. dont touch.

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable : 4996)//WINSOCK_DEPRECATED_NO_WARNINGS

int main() {
	TCHAR Str[10240] = {0,};
	WSADATA WD = { 0, };
	LPHOSTENT HE = nullptr;
	//const char *HN= "www.yahoo.co.jp";
	const char *HN= "localhost.";
	SOCKET S = INVALID_SOCKET;
	SOCKADDR_IN SA = { 0, };
	SOCKADDR_IN CL = { 0, };
	IN_ADDR IA{ {} };


	int E = WSAStartup(2, &WD);
	if (E) { return -1; }
	/** /
	HE = gethostbyname(HN);
	if (HE == nullptr) { return -1; }
	unsigned long IP = 0;
	IP = inet_addr(*HE->h_addr_list);
	if (HE->h_addrtype != AF_INET) { return -1; }
	HE = gethostbyaddr(*HE->h_addr_list, 4, AF_INET);
	/**/
	SA.sin_family = AF_INET;
	SA.sin_addr.S_un.S_addr = inet_addr("127,0,0,1");
	SA.sin_port = htons(23);



	S = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//inet,Socket,TCP.
	if (S == INVALID_SOCKET) { return -1; }
	if(SOCKET_ERROR == bind(S, (SOCKADDR*)&SA, sizeof(SOCKADDR))){return -1;}
	if (listen(S, SOMAXCONN) == SOCKET_ERROR) {return -1;}
	
	//int TT = SA.sin_addr.S_un.S_addr;
	int TT = sizeof(SOCKADDR);
	SOCKET R = accept(S, (SOCKADDR*)&CL, &TT);

	//std::this_thread::sleep_for(std::chrono::seconds(3));

	std::cout << "I got Acssess! " << inet_ntoa(CL.sin_addr) << ":" << CL.sin_port << std::endl;


	shutdown(S, SD_BOTH);
	closesocket(S);
	E = WSACleanup();
	return 0;
}