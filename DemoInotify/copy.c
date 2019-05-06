

#include <sys/inotify.h>
#include <sys/types.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>

#define BUF_LEN (12 * (sizeof(struct inotify_event) + 255 + 1))

char* copy_str(char * str, int t){
   int j=0;
      
   char cadena[t];
   cadena[t]='\0';
   j=t;
    while(j>=0){
       cadena[j]=str[j];
       j--;
    }
    strcpy(str,cadena);
    return str;
}

int is_a_dir(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}


int is_a_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int Exist_Path(char * Ruta_nueva){
   int v=strlen(Ruta_nueva);
   if(is_a_dir(Ruta_nueva)==1 || is_a_file(Ruta_nueva)==1) 
      return 1;
   return 0;  //no existe la ruta
}


int List_contain(char Lista[][200], char * cadenita ,int x){
   
   int t=0;
   int j,i=x;
   for(j=0; j<=x; j++){
        if(strstr( Lista[j], cadenita) != NULL)
           t++;
   }
   return t;
   
}


char* check(char Lista[][200]  ,char* path,int x){
   char *ret = malloc (sizeof (char) * 500);
   strcpy(ret," ");
   int j,i=x;
  for(j=0; j<=x; j++){
      char Ruta_nueva[500]=""; char  Ruta2[10]=""; int tamano=0;
      strcat(Ruta_nueva,Lista[j]);
      tamano=strlen(Lista[j]);
      strncpy(Ruta2 , &Lista[j][strlen(Lista[j])-1],1);
      if(strcmp("/",Ruta2) != 0){
         tamano+=1;
         strcat (Ruta_nueva,"/");
      }
      strcat(Ruta_nueva,path);
      tamano+=strlen(path);
      char * cadenita= copy_str(Ruta_nueva,tamano);
     
     if(List_contain(Lista, cadenita,x)==0 && strstr( Lista[j], cadenita) == NULL && Exist_Path(cadenita)==1 ){ //si no esta en mi cadena de la lista pero existe la ruta es que tengo que añadirlo
         strcpy(Lista[x-1],cadenita);
         strcpy(ret,cadenita);
         break;
      }
        
   }
   return ret;
}


char* check_delete(char Lista[][200]  ,char* path,int x){
   char *ret = malloc (sizeof (char) * 500);
   strcpy(ret," ");
   int j, i=x;
  for(j=0; j<=x; j++){
     
       if( strstr( Lista[j], path) != NULL){ //si no esta en mi cadena de la lista pero existe la ruta es que tengo que añadirlo
        
        if(Exist_Path(Lista[j])==0){
         strcpy(ret,Lista[j]);
         strcpy(Lista[j],"----\0");
         break;
        } 
      }
        
   }
   return ret;
}

char *displayInotifyEvent(struct inotify_event *i)
{
   
	
   if(i->mask & IN_MODIFY) 
		return ("& IN_MODIFY");
		
	if(i->mask & IN_ACCESS)
		 return ("& IN_ACCESS");
		 
	if(i->mask & IN_DELETE)
		return ("& IN_DELETE");
		
	if(i->mask & IN_DELETE_SELF) 
		return ("& IN_DELETE_SELF");
		
	if(i->mask & IN_OPEN) 
		return ("& IN_OPEN");
		
	if(i->mask & IN_MOVED_FROM)
		return ("& IN_MOVED_FROM");
		
	if(i->mask & IN_MOVED_TO)
		return ("& IN_MOVED_TO");
		
	if(i->mask & IN_MOVED_TO)
		return ("& IN_MOVED_TO");
		
	if(i->mask & IN_CLOSE_WRITE)
		return ("& IN_CLOSE_WRITE");
		
	if(i->mask & IN_CLOSE_NOWRITE)
		return ("& IN_CLOSE_NOWRITE");
		
	if(i->mask & IN_ATTRIB)
		return ("& IN_ATTRIB");	
		
   return " ";
}



int main(int argc, char *argv[]) {
   int inotifyFd, xd, j;
   char buf[BUF_LEN];
   ssize_t numRead;
   char *p;
   struct inotify_event *event;
   char *wd[20];
   wd[0]="Lista";
   char Lista[20][200], Lista_primaria[20][200];

   FILE *f = fopen("Midemo.log", "a"); ///var/log/
   fprintf(f, "Iniciando el demonio de monitorizacion de ficheros: \n\n");
  /* if (argc < 2 || strcmp(argv[1], "--help") == 0)
      printf("%s Ruta para el watch... \n", argv[0]);
   */
   inotifyFd = inotify_init(); 
   if (inotifyFd == -1){
		printf("Error Inoty\n");
		fprintf(f, "ERROR en los argumentos.\n");
      fclose(f);
      exit(1);
	}
   fclose(f);
   for (j = 1; j < argc; j++) {
      xd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);
      wd[xd] = argv[j];
      if (xd == -1)
        printf("Error");
      else{
         FILE *f = fopen("Midemo.log", "a"); ///var/log/
         fprintf(f,"\n*****************\nActivando Eventos para= %s \n*****************\n", argv[j]);
         fclose(f);
      }
      //printf("Watch en %s con wd=%d   \n", argv[j], 1);
      strcpy(Lista[j-1] , argv[j]);
      strcpy(Lista_primaria[j-1] , argv[j]);
      printf("Lista %s\n", Lista[j-1]);
   }
   
   char ruta[200];
   for (;;) { 
      numRead = read(inotifyFd, buf, BUF_LEN);
      if (numRead == 0)
         printf("Error");
      if (numRead == -1)
         printf("Error");
      
      for (p = buf; p < buf + numRead; ) {
         event = (struct inotify_event *) p;
         char* comp2=displayInotifyEvent(event);
         char buff2[100];
          time_t now = time (0);
          strftime (buff2, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));
         if(event->mask & IN_CREATE){
       		char ruta[strlen(event->name)];//=wd[xd];
       		strcpy(ruta,event->name);
       		char* comp=check(Lista,ruta,j);
       		if(strcmp(" ",comp) != 0){
       		   j++;
       		   int v=inotify_add_watch(inotifyFd,comp, IN_ALL_EVENTS);
       		   wd[event->wd]=comp;
          		if (v == -1)
                  printf("Error");
               else{
                  FILE *f = fopen("Midemo.log", "a"); ///var/log/
               	fprintf(f,"\n*****************\n%s Activando Eventos para= %s \n*****************\n",buff2, comp);
               	fprintf(f,"%s Evento captado en la ruta :  %s, Evento: IN_CREATE \n", buff2, comp);
               	fclose(f);
               }
       		}
            
         }
         else{
             if(event->mask & IN_DELETE){
                int k;
                 for(k=0; k<=j; k++){
                     printf("Lista: [%d] =%s\n",k,Lista[k]);
                      }
                  char ruta[strlen(event->name)];//=wd[xd];
       		      strcpy(ruta,event->name);
                  char* comp=check_delete(Lista,ruta,j );
                  if(strcmp(" ",comp) != 0){
                     
                     
                  }
                 for(k=0; k<=j; k++){
                     printf("Lista: [%d] =%s\n",k,Lista[k]);
                      }
             }
            else{
               if(strcmp(" ",comp2) != 0 && wd[event->wd]!= NULL){
                  FILE *f = fopen("Midemo.log", "a"); ///var/log/
                  fprintf(f,"%s Evento captado en la ruta :  %s, Evento: %s \n",buff2, wd[event->wd],comp2);
                  fclose(f);
               }
            }
               
         }
      	  p += sizeof(struct inotify_event) + event->len;
        
      }
   }
   exit(0);
}



