#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include <stdbool.h>
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<fcntl.h>
//#define MAX_BUF_LEN 1024    
#define MAX_ARGS 100
char* args[MAX_ARGS];


char* get_input();
char** parsing_arguments(char* line);
void exec_commands(char** args);
bool check_args(char** args);
void redirection(char** args);
void controlpipes(char** args);

size_t max_buff =1024;   
bool ex_prog; 
int num_args;

int main() 
{
  bool redir=false,pip=false;
 
  char* line=(char*)malloc(max_buff*sizeof(char*));
  ex_prog=false;
  
  while(1)
  {
    line=get_input();
    parsing_arguments(line);
    ex_prog=check_args(args);
    if(ex_prog){
      exit(0);
    }else{
     
      for(int i=0;i<num_args;i++)
      {
        if((strcmp(args[i],">")==0)||(strcmp(args[i],">>")==0)||(strcmp(args[i],"<")==0))
        {
          redir=true;
        }
        if ((strcmp(args[i],"|")==0))
        {
          pip=true;
        }
      }
      if(redir==true){
        redirection(args);
        redir=false;
      }else if(pip){
        controlpipes(args);
        pip=false;
      }else
      {
        exec_commands(args);
      }
    }
  }
  
  

}

bool check_args(char** args)
{
  bool ex_prog=false;
  if((strcmp(args[0],"exit")==0)){
    ex_prog=true;

  }
  if(num_args>=MAX_ARGS){
    ex_prog=true;
    printf("You gave too many arguments.");
  }
  

  return ex_prog;

}

char* get_input()
{
  char* line;
  line = (char*)malloc(max_buff*sizeof(char*)); 
  
  printf("$");
  getline(&line,&max_buff,stdin);
  if(line[0]==0x0A)
  {
    printf("You gave no arguments.\n");
    exit(0);
  }
  return line;

}

char** parsing_arguments(char* line)
{
  
  char* token;
  int pos=0;

  token = strtok(line, " \n");
  while (token != NULL) {
    args[pos] = token;
    pos++;
    token = strtok(NULL, " \n");
  }
  num_args=pos-1;
  args[pos] = NULL;
  
  return args;

}

void exec_commands(char** args)
{
  
  pid_t pid = fork();
  int status;
  if (pid < 0)
  {
    perror("fork error");
    exit(EXIT_FAILURE);
  }
  if(pid==0){
    execvp(args[0],args); 
    if (execvp(args[0],args) == -1) {
      printf("%s",args[0]);
      perror("lsh");
    }
  }
  

  waitpid(pid,&status,0);
  printf("child with pid %d terminated with exit status %d\n",pid,status);
}

void redirection(char** args)
{
  pid_t pid=fork();

  int i=0,status;
  int fd1,fd2,size,fd;
  char* filename=(char*)malloc(30*sizeof(char));
  char* filename1=(char*)malloc(30*sizeof(char));
  if(pid<0)
  {
    perror("fork error");
    exit(1);

  }
  else if(pid==0)
  {
   while(i<num_args)
   {
     if(strcmp(args[i],"<")==0)
     {
       strcpy(filename1,args[i+1]);
       fd2=open(filename1,O_RDONLY,S_IRWXU);
       dup2(fd2,fileno(stdin));
       args[i]=NULL;
     }
     else if((strcmp(args[i],">")==0))
     {
       strcpy(filename,args[i+1]);
       fd1=open(filename,O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
       dup2(fd1,fileno(stdout));
       args[i]=NULL;
      
    
      }
      else if( (strcmp(args[i],">>")==0))
     {
       strcpy(filename,args[i+1]);
       fd1=open(filename,O_RDWR|O_APPEND|O_CREAT,S_IRWXU);
       dup2(fd1,fileno(stdout));
       args[i]=NULL;
      }
     i++;
    }
  
    execvp(args[0],args); 
    exit(0);
  }else{
   waitpid(pid, NULL, 0);
   
       
  
   
    free(filename);
    free(filename1);
  }
}

void controlpipes(char** args)
{
  
  int i=0,num_pipes=0;
  bool redirect;
  char* filename=(char*)malloc(30*sizeof(char));
  for( i;i<num_args;i++)
  {
    if((strcmp(args[i],"|")==0))
    {
      num_pipes++;
    }
    
  }
  
  args[i+1]="|";
    
  int j=0,k=0;
  int fd[2],fd1;
	pid_t pid;
	int fdd = 0;
  char* cmd[20];
  i =0;

  
  while(j<=num_pipes)

  {
    while((strcmp(args[i],"|")!=0))
    {
      cmd[k]=args[i];
      i++;
      k++;
    }
    cmd[k]=NULL;

    pipe(fd);
    if((pid=fork())==-1)
    {
      perror("fork");
      exit(1);
    }
    else if(pid==0)
    {
      dup2(fdd,0);
      if(j<num_pipes)
      {
        dup2(fd[1],1);
      }
      
      close(fd[0]);
    
      execvp(cmd[0],cmd);
      exit(0);
            
    }
    else
    {
      waitpid(pid,NULL,0);
      close(fd[1]);
      fdd=fd[0];
            
    }
        
    k=0;
    i++;
    j++;

  }
 
    


   
}

