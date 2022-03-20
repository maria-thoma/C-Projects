#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

typedef struct date
{
    int day, month, year;
}date;

typedef struct director_info
{
    char* director_surname, *director_name;  
}director_info;


typedef struct movie
{
    int id;
    char *title;
    director_info* director;
    date*release_date;
}movie;

int size;
void menu();
movie* read_movies();
movie* insert_movie(movie* array);
int delete_movie(movie* array);
int search_movie_title(movie* mv);
int search_movie_director(movie* mv);
int exit_movie(movie *array);
void check_files(FILE *fp);
void check_close_files(FILE *fp);



int main(int argc, char *argv[])
{
    menu();

    return 0;
   
}

void menu(){
    int op=1;
     movie* array;
     array = read_movies();
  
    while(op!=5){
        printf("1.Insert a new movie\n");
        printf("2.Delete a movie based on movie’s id\n");
        printf("3.Search a movie based on movie’s title\n");
        printf("4.Search a movie based on movie’s director\n");
        printf("5.Exit\n");
        printf("Choose an option:");
        scanf("%d",&op);
       if(op<=5 && op>=1){
    
          switch (op)
          {
            case 1:
              system("clear");
              insert_movie(array);
             break;
            case 2:
              system("clear");
              delete_movie(array);
             break;
            case 3:
             system("clear");
             search_movie_title(array);
             break;
            case 4:
             system("clear");
             search_movie_director(array);
             break;
            case 5:
             system("clear");
             exit_movie(array);
             break;
            default:
             break;
        }


    }else{
        printf("\nThere is no option\n");
    }
    }



}

movie* read_movies()
{
    movie *array;
    array = (movie*) malloc (sizeof(movie) * 100);
    int i=0;
    
    FILE *fp;
    fp = fopen("movies.txt","r+");
    check_files(fp);
    while(!feof(fp)){
        (array+i)->title = (char*) malloc (sizeof(char) * 50 );
        (array+i)->director=(director_info*) malloc (sizeof(director_info));
        (array+i)->director->director_name=(char*)malloc(sizeof(char)*15);
        (array+i)->director->director_surname=(char*) malloc (sizeof(char)*15);
        (array+i)->release_date=(date*)malloc(sizeof(date));
        fscanf(fp,"%d",&(array+i)->id);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%[^\n]",(array+i)->title);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%[^\n]",(array+i)->director->director_surname);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%[^\n]",(array+i)->director->director_name);
        fseek(fp,1,SEEK_CUR);
        fscanf(fp,"%d\n%d\n%d\n",&(array+i)->release_date->day,&(array+i)->release_date->month,&(array+i)->release_date->year);
        i++;
    }
      

    size=i;

    check_close_files(fp);
    
    return array;
}

movie* insert_movie(movie* array)
{
    movie mv1;
    
   
    mv1.title=(char*)malloc(50*sizeof(char));
    mv1.director=(director_info*)malloc(sizeof(director_info));
    mv1.director->director_surname=(char*)malloc(15*sizeof(char));
    mv1.director->director_name=(char*)malloc(15*sizeof(char));
    mv1.release_date=(date*)malloc(sizeof(date));
    
    srand ( time(NULL) );
    mv1.id = (rand() % (9999-1000 +1) + 1000);
   // int c; 
  //  c = getchar();
    printf("Give movie's title: ");
    scanf("%[^\n]",mv1.title);
    printf("Give director's surname: ");
    scanf("%s",mv1.director->director_surname);
    printf("Give director's name: ");
    scanf("%s",mv1.director->director_name);
    printf("Give  release date(dd/mm/yy): ");
    scanf("%d/%d/%d",&mv1.release_date->day,&mv1.release_date->month,&mv1.release_date->year);
    system("clear");
    
   

    (array+size)->title = (char*) malloc (sizeof(char) * 50 );
    (array+size)->director=(director_info*) malloc (sizeof(director_info));
    (array+size)->director->director_name=(char*)malloc(sizeof(char)*15);
    (array+size)->director->director_surname=(char*) malloc (sizeof(char)*15);
    (array+size)->release_date=(date*)malloc(sizeof(date));

    (array+size)->id=mv1.id;
    (array+size)->title=mv1.title;
    (array+size)->director->director_surname=mv1.director->director_surname;
    (array+size)->director->director_name=mv1.director->director_name;
    (array+size)->release_date->day=mv1.release_date->day;
    (array+size)->release_date->month=mv1.release_date->month;
    (array+size)->release_date->year=mv1.release_date->year;
    size++;

 
    return array;
    

}
        
int delete_movie(movie* array)
{
    int iddel,i=0,pos=0;
    bool find=false;

    printf("Give the movie's id you want to delete: ");
    scanf("%d",&iddel);
    for(i;i<size;i++){
        if((array+i)->id==iddel){
            find=true;
            puts("find");
            pos=i;
        }
    }
    
    int c;
    if(find){
        for (c = pos ; c < size-1; c++){
         array[c] = array[c+1];
        
        }
        size--;
    
        return 0;


    }else{
        printf("This movie does not exist");
        return 1;
        
    }
    system("clear");

}

int search_movie_title(movie* mv)
{
    bool find=false;
    int pos=0;
    char* t;
    t=(char*)malloc(20*sizeof(char));
   // int c; 
  //  c = getchar(); 
    printf("Give the movie's title you want to find: ");
    scanf("%[^\n]",t);
    system("clear");
    int i=0;
    for(i;i<size;i++){
        if((strcmp(t,(mv+i)->title)==0)){
           find=true;
           pos=i;
        }
        
    }
   
    if(find){
        printf(" Movie id: %d\n Movie title: %s\n Director: %s %s\n",mv[pos].id,mv[pos].title,mv[pos].director->director_name,mv[pos].director->director_surname);
        printf(" Release date: %d/%d/%d\n",mv[pos].release_date->day,mv[pos].release_date->month,mv[pos].release_date->year);
        return 0;
    
    } else{ 
        puts("Doesn't exist");
        return 1;
    }
    system("clear");

} 

int search_movie_director(movie* mv)
{
    char* name;
    char* s_name;
    bool find=false;
    int i=0,pos=0;

    name = (char*)malloc(15*sizeof(char));
    s_name = (char*)malloc(15*sizeof(char));

    printf("\nDirector's name: ");
    scanf("%s",name);
    printf("\nDirector's surname: ");
    scanf("%s",s_name);

    for(i;i<size;i++){
        if((strcmp((mv+i)->director->director_name,name)==0)){
            if((strcmp((mv+i)->director->director_surname,s_name)==0)){
                find=true;
                pos=i;

            }
        }

    }
    if(find){
        printf(" Movie id: %d\n Movie title: %s\n Director: %s %s\n",mv[pos].id,mv[pos].title,mv[pos].director->director_name,mv[pos].director->director_surname);
        printf(" Release date: %d/%d/%d\n",mv[pos].release_date->day,mv[pos].release_date->month,mv[pos].release_date->year);
        return 0;
    
    } else{ 
        puts("Doesn't exist");
        return 1;
    }


}

int exit_movie(movie *array)
{
    FILE *fp;

    fp  = fopen("movies.txt","w");
    check_files(fp);
    rewind(fp);
    int i=0;

    while(i<size){
        
        fprintf(fp,"%d\n",(array+i)->id);
        
        fprintf(fp,"%s\n",(array+i)->title);
        
        fprintf(fp,"%s\n",(array+i)->director->director_surname);
        
        fprintf(fp,"%s\n",(array+i)->director->director_name);
        
        fprintf(fp,"%d\n%d\n%d\n",(array+i)->release_date->day,(array+i)->release_date->month,(array+i)->release_date->year);
        
        i++;
    }

 
   check_close_files(fp);


}

void check_files(FILE *fp)
{
    if(fp==NULL){
        printf("Error number: %d\n",errno);
        perror("open failed:");
        exit(1);
    }
}

void check_close_files(FILE *fp)
{
    if (fclose(fp) != 0){
        printf("Error number: %d\n",errno);
        perror("close failed:");
        exit(1);
    }
}










