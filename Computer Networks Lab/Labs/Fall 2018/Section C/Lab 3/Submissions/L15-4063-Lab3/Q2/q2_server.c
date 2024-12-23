#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;
        
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        
        while(1) {
        
        char server_message[2000], client_message[2000];

        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        //Accept the incoming Connections
        
        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
        
        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return -1;
        }
        
        printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        
        //Receive the message from the client
        
        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Client Message: %s\n",client_message);
        
        //Send the message back to client
        
        int i = 0;
        int j = 0;
        int k = 0;
        int words[50];
        words[0] = 0;
        
        j = 1;
        for( i = 0; i<strlen(client_message); i++)
        {
        	if(client_message[i] == ' ')
        	{
        		words[j] = i;
        		j++;
        	}
        }
        int totalwords = i;
        
        for (i = 0; i < words[k+1]; i++)
        {
        	if(client_message[i]=='a' || client_message[i]=='e'  || client_message[i]=='i' || client_message[i]=='o' || client_message[i]=='u'|| 
            client_message[i]=='A' || client_message[i]=='E'  || client_message[i]=='I' || client_message[i]=='O' || client_message[i]=='U')
            {
            	int l = words[k+1];
            	for(j=words[k]; j< words[k+1]; j++)
            	{
            		char temp = client_message[j];
            		client_message[j] = client_message[l];
            		client_message[l] = temp;
            		l--;
            	}
            }
            k++;
        }
        
        /*while(i<strlen(client_message))
        {
        	if(client_message[i]=='a' || client_message[i]=='e'  || client_message[i]=='i' || client_message[i]=='o' || client_message[i]=='u'|| 
            client_message[i]=='A' || client_message[i]=='E'  || client_message[i]=='I' || client_message[i]=='O' || client_message[i]=='U')
            {
            	
            	for(i=0; i< word_index; i++)
            	{
            	printf("in for invert     ");
            		temp = client_message[i];
            		client_message[i] = client_message[j];
            		client_message[j] = temp;
            	}
            	prev_word = word_index;
            }
            else
            {
            	i++;
            }               
        }*/
        
        
        if (send(client_sock, client_message, strlen(client_message),0)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
              
              
        }      
              
        //Closing the Socket
        
        close(client_sock);
        close(socket_desc);
        return 0;       
}
