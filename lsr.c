#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ls(char* fileName, char* nameString) {
	/* create DIR* dp, dirent* ent */
	DIR* dp;
	struct dirent* dent;

	strcat(nameString, fileName); 			// add filename to nameString

	printf("%s:\n\n", nameString);			// print current location

	if ((dp = opendir(fileName)) == NULL) {	// if opendir fail, error return
		perror("opendir");
		exit(1);
	}

	chdir(fileName);						// change dir(filename)

	while ((dent = readdir(dp))) {			// read files in directory
		if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0) 	// skip print when d_name is '.', '..'
			continue;

		printf("%s ", dent->d_name);											// print directory name
	}

	printf("\n");
		
	rewinddir(dp);							// set directory pointer to front

	while ((dent = readdir(dp))) {			// read files in directory again
		if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)	// skip when d_name is '.', '..'
			continue;

		struct stat buf;					// file stat -> buf

		stat(dent->d_name, &buf);			// insert d_name stat -> buf

		if (buf.st_mode & S_IFDIR) {		// if d_name is a directory
			printf("\n\n");
			char* before = malloc(strlen(nameString) + 4);	// save nameString before ls(d_name)
			strcpy(before, nameString);
			strcat(nameString, "/");						// add nameString + '/'

			ls(dent->d_name, nameString);	// ls (d_name, nameString)
			
			strcpy(nameString, before);		// when finish ls, nameString must also return to its previous state.
			free(before);					// memory free
		}
	}

	chdir("..");							// if function finished, change dir to before dir

	closedir(dp);
}

int main(int argc, char* argv[]) {
	char* fn;										// fileName string
	char* nameString = malloc(sizeof(char) * 1000);	// allocate memory
	struct stat buf;								// file stat -> buf
	strcpy(nameString, ""); 						// reset nameString
	if (argc > 1){									// if program get arguments, repeat ls by the argument's number.
		for (int i = 1; i < argc; i++){
			fn = argv[i];							// save arguments in fn
			
			if (stat(fn, &buf) == -1) {				// get fn's stat, if error occurs, print error and go to front of loop.
				/* make error message */
				char* tmp = malloc(sizeof(char) * 200);
				strcpy(tmp, "ls: cannot access '");
				strcat(tmp, fn);
				strcat(tmp, "'");
				perror(tmp);
				free(tmp);
				continue;
			}			

			if (!(buf.st_mode & S_IFDIR)){			// if fn is not a directory
				printf("%s\n",fn);					// print fileName
				continue;							// go to front of loop
			}

			ls(fn, nameString); 					// run ls
			strcpy(nameString, "");					// reset nameString
		}
	}
	else {											// if there is no argument, do ls for the current path.
		fn = ".";									
		ls(fn, nameString);
	}
	
	free(nameString);								// memory free
	return 0;
}