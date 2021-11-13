#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ls(char* fileName, char* nameString) {
	DIR* dp;
	struct dirent* dent;

	if ((dp = opendir(fileName)) == NULL) {
		perror("opendir");
		exit(1);
	}

	chdir(fileName);

	chdir(filename);

	while ((dent = readdir(dp))) {
		if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)
			continue;

		printf("%s ", dent->d_name);
	}

	printf("\n");
		
	rewinddir(dp);

	while ((dent = readdir(dp))) {
		struct stat buf;

		if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)
			continue;

		struct stat buf;

		stat(dent->d_name, &buf);

		if (buf.st_mode & S_IFDIR) {
			printf("\n\n");
			char* before = malloc(strlen(nameString) + 4);
			strcpy(before, nameString);
			strcat(nameString, "/");

			ls(dent->d_name, nameString);
			
			strcpy(nameString, before);
			free(before);
			
		}
	}

	chdir("..");

	closedir(dp);
}

int main(int argc, char* argv[]) {
	char* fn;
	char* nameString = malloc(sizeof(char) * 1000);
	strcpy(nameString, "");
	if (argc > 1){
		for (int i = 1; i < argc; i++){
			fn = argv[i];
			ls(fn, nameString);
			strcpy(nameString, "");
		}
	}
	else {
		fn = ".";
		ls(fn, nameString);
	}
	
	free(nameString);
	return 0;
}