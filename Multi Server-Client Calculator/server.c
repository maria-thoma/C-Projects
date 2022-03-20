#include <stdio.h>  
#include <string.h>   
#include <stdlib.h>  
#include <errno.h> 
#include <stdbool.h> 
#include <unistd.h>     
#include <arpa/inet.h>     
#include <sys/types.h>  
#include <sys/socket.h>   
#include<sys/wait.h> 
#include <netinet/in.h>


//#define PORT 3333
bool valid=true;
double calculator(char* buff);
int main(int argc, char* argv[])
{
    int sockfd,newSocket,ret,status;
    socklen_t addr_size;
    char  msg[]="Invalid operation";
    double result;
    char operation[10];
    struct sockaddr_in serverAddr,newAddr;
    pid_t childpid;
    serverAddr.sin_family=AF_INET;
    
    serverAddr.sin_port=htons(atoi(argv[1]));
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        printf("Error in connection\n");
        exit(1);
    }else
    {
        printf("Server socket is created!\n");
    }
    
    ret=bind(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    if(ret<0)
    {
        printf("Error in binding\n");
        exit(1);

    }

     if(listen(sockfd,10)==0)
     {
        printf("Listening..\n");
     }
     else{
        printf("Error in listening..");
        exit(1);
    }


    while(1)
    {
    
        newSocket=accept(sockfd,(struct sockaddr *)&newAddr,&addr_size);
        if(newSocket<0)
        {
            exit(1);
        }
        printf("Connection accepted \n");
      
        
        childpid = fork();
        if(childpid==0)
        {
            close(sockfd);
            while(1)
            {
                recv(newSocket,operation,10,0);
                
                if(strcmp(operation,"exit")==0)
                {
                    printf("CLient Disconected from server\n");
                    break;
                }else{
                
                    printf("CLient sent:%s\n",operation);
                    result=calculator(operation);  
                    send(newSocket,&valid,sizeof(valid),0); 
                    if(valid)
                    {



                        result=calculator(operation);                
                        send(newSocket,&result,sizeof(result),0);
                        fflush(stdin);
                    }
                }

            }
        }
         
    }
    close(sockfd);
    unlink(argv[1]);
   
 }


double calculator(char* buff)
{
    char operand;
    char* args[10];
    char *token,op;
    double num1,num2;
    double result;
    char* msg;
    valid=true;
    
    msg=(char*)malloc(20*sizeof(char));    

    token = (char*) malloc(20*sizeof(char));

    
    for(int i=0;i<strlen(buff);i++)
    {
        if((buff[i]=='+') ||( buff[i]=='-') ||(buff[i]=='*')||(buff[i]=='/'))
        {
            operand=buff[i];
        
           buff[i]=' ';
            
            
        }
        
    }
    token=strtok(buff," ");
    int i=0;
    while(token!=NULL)
    {
        args[i]=token;
        i++;
        token=strtok(NULL," ");


        
    }
    num1=atoi(args[0]);
    num2=atoi(args[1]);
    if((operand=='/')&&(num2==0))
    {
        valid=false;
    }
    else{
        switch (operand)
        {
            
            case '*':
                result=num1*num2;
                break;
            case '+':
               result=num1+num2;
                break;
             case '-':
               result=num1-num2;
                break;
             case '/':
               if(num2!=0)
                result=num1/num2;
               else {
                strcpy(msg,"error");
                return result;
               }
             break;
            
             default:
                break;
            

        }
    }

     

    return result;
    
}