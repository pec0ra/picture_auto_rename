#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/inotify.h>

#define EVENT_SIZE 		(sizeof (struct inotify_event))
#define EVENT_BUF_LEN		( 1024 * ( EVENT_SIZE + 16 ) )

#define COMMAND			"jhead "
#define FORMAT			"-n%Y/%y.%m.%d-%H.%M.%S "

char *escape_name(char *old_name){
	int count = 0;
	char *t;
	for(t=old_name; *t; t++)
		count += (*t == ' ');

	char *res = malloc(strlen(old_name) + count);
	char *ptr = res;
	for(t=old_name; *t; t++) {
		if(*t == ' ') {
			memcpy(ptr, "\\\\", 1);
			ptr += 1;
			memcpy(ptr, " ", 1);
			ptr += 1;
		} else {
			*ptr++ = *t;
		}
	}
	*ptr = 0;
	return res;
}

int is_jpeg(char *name){
	int length = strlen(name);
	char ext[4];
	strcpy(ext, &name[length -4]);
	return !strcmp(ext, ".JPG") || !strcmp(ext, ".jpg");
}

int run(char *directory){
	int event_length, i;
	int fd;
	int wd;
	char buffer[EVENT_BUF_LEN];
	char command[100];
	char *name;


	if((fd = inotify_init()) < 0){
		perror( "inotify_init" );
		return 1;
	}


	printf("%s\n", directory);
	if((wd = inotify_add_watch( fd, directory, IN_CLOSE_WRITE | IN_MOVED_TO)) < 0){
		perror( "inotify_add_watch");
		return 1;
	}
		
start:
	i = 0;
	event_length = read( fd, buffer, EVENT_BUF_LEN);
	if(event_length < 0){
		perror( "read");
	} else {
		while( i < event_length ){
			struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
			if ( event->len ) {
				if(is_jpeg(event->name)){
					name = escape_name(event->name);
					strcpy(command, COMMAND);
					strcat(command, FORMAT);
					strcat(command, directory);
					strcat(command, "/");
					strcat(command, name);
					sleep(2);
					system(command);
				}
			}

			i += EVENT_SIZE + event->len;
		}
	}
	goto start;
	
}
