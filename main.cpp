#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
using namespace std;

#ifdef WIN32
#include <windows.h>
#endif

extern "C" {
#include <web_server.h>
}

#include "main.h"

int PORT=1024;

sqlite *db;
char *zErrMsg = 0;
int rc;

void logfile() {
	FILE *log;
	printf("Content-type: text/plain \r\n\r\n");
	web_client_addfile("./demo.log");
	printf("Fim do log\n");
};

int main() {

	int pid;
	struct web_server server;
	
	
	
	while(!web_server_init(&server,PORT,"",0)) {
		PORT++;	
	};
	printf("http://localhost:%d\n",PORT);
	
	
	db = sqlite_open("supra.dat", 0, &zErrMsg);
	
	web_server_addhandler(&server,"* /",index_html,WS_LOCAL);
	web_server_addhandler(&server,"* /search",search_html,WS_LOCAL);
	web_server_addhandler(&server,"* /time",time_html,WS_LOCAL);
	web_server_addhandler(&server,"* /img/bg1.jpg",bg1_jpeg,WS_LOCAL);
	web_server_addhandler(&server,"* /info",info_html,WS_LOCAL);
	web_server_run(&server);

//	ofstream eout("portno");
//	eout << PORT <<endl;
	cout << "Ovaj program je pretrazivac Interne sudske prakse " << endl;
	cout << "Opcinskog suda u Zagrebu" << endl << endl;
	
	cout << "Kada zavrsite sa pretrazivanjem, zatvorite ovaj prozor" << endl;
	//cout << "Windows 98 i Windows Me ce vas pitati 
	
	//cout << "http://localhost:" << PORT<< endl;	
	//fsync();
#ifdef WIN32
	char cmd[100];
	sprintf(cmd, "http://localhost:%d", PORT);
	ShellExecute(NULL,"open",cmd,NULL,NULL,SW_SHOWNORMAL); 
#endif
	//web_server_addhandler(&server,"* /search",search_html,0);
	//web_server_addhandler(&server,"* /log",logfile,0);
	while(1) {
		// DO whatever u want
	//	cout << "test" << endl;		
		web_server_run(&server); // Process web_server
	
	};



	
	return 0;

};
