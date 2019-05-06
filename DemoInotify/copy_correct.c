

#include <sys/inotify.h>
#include <sys/types.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 



static void displayInotifyEvent(struct inotify_event *i)
{
	printf("wd= %2d   ", i->wd);
	if(i->cookie>0)
	printf("cookie= %4d ", i->cookie);
	printf("mask= ");
	if(i->mask & IN_CREATE) printf(" IN_CREATE");
	if(i->mask & IN_MODIFY) printf(" IN_MODIFY");
	if(i->mask & IN_ACCESS) printf(" IN_ACCESS");

	if(i->mask & IN_DELETE) printf(" IN_DELETE");
	if(i->mask & IN_DELETE_SELF) printf(" IN_DELETE_SELF");
	if(i->mask & IN_OPEN) printf(" IN_OPEN");
	if(i->mask & IN_MOVED_FROM) printf(" IN_MOVED_FROM");
	if(i->mask & IN_MOVED_TO) printf(" IN_MOVED_TO");
	if(i->mask & IN_MOVED_TO) printf(" IN_MOVED_TO");
	if(i->mask & IN_CLOSE_WRITE) printf(" IN_CLOSE_WRITE");
	if(i->mask & IN_CLOSE_NOWRITE) printf(" IN_CLOSE_NOWRITE");

	if(i->mask & IN_ATTRIB) printf(" IN_ATTRIB");
	printf("\n");
	if(i->len >0) printf("name= %s\n", i->name); //si es mayor que cero significa que estamos

}


#define BUF_LEN (10 * (sizeof(struct inotify_event) + 255 + 1))
int
main(int argc, char *argv[]) {
int inotifyFd, wd, j;
char buf[BUF_LEN];
ssize_t numRead;
char *p;
struct inotify_event *event;

if (argc < 2 || strcmp(argv[1], "--help") == 0)
   printf("%s Ruta para el watch... \n", argv[0]);

inotifyFd = inotify_init(); 
if (inotifyFd == -1)
   printf("Error");

for (j = 1; j < argc; j++) {
   wd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);
   if (wd == -1)
      printf("Error");
   printf("Watch en %s con wd=%d\n", argv[j], wd);
}

for (;;) { 
   numRead = read(inotifyFd, buf, BUF_LEN);
if (numRead == 0)
   printf("Error");
if (numRead == -1)
   printf("Error");

   for (p = buf; p < buf + numRead; ) {
      event = (struct inotify_event *) p;
      displayInotifyEvent(event);
      p += sizeof(struct inotify_event) + event->len;
   }
}
exit(0);
}