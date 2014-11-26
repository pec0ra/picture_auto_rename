#include <unistd.h>
#include <stdio.h>
#include "picture_auto_rename.h"

int main(int argc, char **argv){

// 	if(geteuid() != 0)
// 	{
// 		printf("Error : Picture auto rename must be run as root !\n");
// 		return 0;
// 	}

	if(argc == 2){
		char *directory = argv[1];
	 	if(!daemon(0, 0)){
	 		run(directory);
	 	} else {
			printf("Failed to start daemon");
		}
	}
	return 1;
}
