#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include "chat.h"

#define BLANK "                                                                         "
#define MSG_ROW 42
#define MSG_COL 24

char serv_player;

void set_serv_player(char p){
	serv_player = p;
}

void chatting(char* hostname, int portnum){
	move(MSG_ROW+1,MSG_COL-14);
	addstr(BLANK);
	move(MSG_ROW+1,MSG_COL-14);
	addstr("send message: ");
	refresh();

	chat_clnt(hostname, portnum);
}
  
#define HOSTLEN		256
#define oops(msg)	{perror(msg); exit(1);}
void* chat_serv(void* port){
	int portnum = *(int *)port;
	struct sockaddr_in	saddr;
	struct hostent		*hp;
	char hostname[HOSTLEN];
	int sock_id, sock_fd;
	FILE *sock_fp;
	char message[BUFSIZ];
//	char c;

	/* get a socket */
	sock_id = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_id == -1)
		oops("socket");

	/* bind address to socket */
	bzero( (void*)&saddr, sizeof(saddr) );
	
	gethostname(hostname, HOSTLEN);
	hp = gethostbyname(hostname);

	bcopy( (void*)hp->h_addr, (void*)&saddr.sin_addr, hp->h_length);
	saddr.sin_port = htons(portnum);
	saddr.sin_family = AF_INET;

	if( bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0 )
		oops("bind");

	/* allow incoming call */
	if( listen(sock_id, 1) != 0 )
		oops("listen");
		
	while(1){
		sock_fd = accept(sock_id, NULL, NULL);
		if( sock_fd == -1 )
			oops("accept");	

		sock_fp = fdopen(sock_fd, "r");
		if( sock_fp == NULL )
			oops("fdopen");
		
		move(MSG_ROW,MSG_COL-3);
		if(serv_player == 'A')
			addstr("B: ");
		else if(serv_player == 'B');
			addstr("A: ");		
		move(MSG_ROW,MSG_COL);
		addstr(BLANK);
		move(MSG_ROW,MSG_COL);
		fgets(message, BUFSIZ, sock_fp);
		addstr(message);
		refresh();

		fclose(sock_fp);
	}
}

void chat_clnt(char* hostname, int portnum){
	struct sockaddr_in	servadd;
	struct hostent		*hp;
	int sock_id;
	FILE* sock_fp;
	char message[BUFSIZ];

	echo();

	sock_id = socket(AF_INET, SOCK_STREAM, 0);
	if( sock_id == -1 )
		oops("socket");

	bzero(&servadd, sizeof(servadd));

	hp = gethostbyname(hostname);
	if(hp == NULL)
		oops(hostname);
	bcopy(hp->h_addr, (struct sockaddr*)&servadd.sin_addr, hp->h_length);

	servadd.sin_port = htons(portnum);

	servadd.sin_family = AF_INET;

	if(connect(sock_id, (struct sockaddr*)&servadd, sizeof(servadd)) != 0)
		oops("connect");

	sock_fp = fdopen(sock_id, "w");

	getstr(message);
	fprintf(sock_fp, "%s", message);
	fflush(sock_fp);
	fclose(sock_fp);

	noecho();
}
