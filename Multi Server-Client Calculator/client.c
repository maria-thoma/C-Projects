#include <stdio.h>  
#include <string.h>    
#include <stdlib.h>  
#include <errno.h> 
#include <stdbool.h>  
#include <unistd.h>    
#include <arpa/inet.h>   
#include <sys/types.h>  
#include <sys/socket.h>  

int main(int argc, char* argv[])
{
    int server_sockfd,ret,i; 
    struct sockaddr_in addr;
    char operation[10];
    double result;
    bool valid;



    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[1]));
    inet_aton(argv[2],&addr.sin_addr);
   
   // addr.sin_port=htons(PORT);
   // addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  
    server_sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(server_sockfd<0)
    {
       printf("Error Conention!\n");
       exit(1);
    }
    ret=connect(server_sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret<0)
    {
        printf("Connect error\n");
        exit(1);
    }
    printf("Client connected to server!\n");    
    while(1)
    {
        printf("Give the operation: ");
        scanf("%s",operation);
        send(server_sockfd,operation,10,0);
        //fflush(stdin);
        if(strcmp(operation,"exit")==0)
        {
            printf("Client Disconnected\n");
            
            close(server_sockfd);
            unlink(argv[1]);
            exit(0);
        }else
        {
           recv(server_sockfd,&valid,sizeof(valid),0); 
           
           if(valid)
           {
            recv(server_sockfd,&result,sizeof(result),0);
            printf("The result is: %f\n",result);
            fflush(stdin);

           }else
           {
               printf("Invalid operation\n");
               
           }
           
           
           
           
        }
        
    
        
        

        
    }
    
    return 0;


    


    




    
}
