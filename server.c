#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
int main()
{
	int fd = 0;
	char buff[1024];
	char nbuff[1024];
	memset(buff, '0',sizeof(buff));	
	fd = socket(AF_INET, SOCK_STREAM, 0);
    	if(fd<0)
	{
		perror("Client Error: Socket not created succesfully");
		return 0;
	}
	struct sockaddr_in server; 
	memset(&server, '0', sizeof(server)); 
	server.sin_family = AF_INET;
	server.sin_port = htons(10011); 
        server.sin_addr.s_addr = htonl(INADDR_ANY);
   

	bind(fd, (struct sockaddr*)&server, sizeof(server)); 

	int in;
	
	listen(fd, 10); 
	while(	in = accept(fd, (struct sockaddr*)NULL, NULL))
	{		
		int childpid,n;
		if ( (childpid = fork ()) == 0 ) 
		{
		
			close (fd);
			bzero(buff,256);
			bzero(nbuff,256);
							
			while ( (n = recv(in, buff, 256,0)) > 0)  
			{
			
				printf("Server Received: %s",buff);
				
				char *nbuff = strrev(buff);
				send(in, nbuff, strlen(nbuff), 0);
		
				bzero(buff,256);
										
			}
			close(in);
			exit(0);
		}
		
	}
}
