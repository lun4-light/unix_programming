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

	strcat(nameString, fileName);

	printf("%s:\n\n", nameString);

	if ((dp = opendir(nameString)) == NULL) {
		perror("opendir");
		exit(1);
	}

	while ((dent = readdir(dp))) {
		if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)
			continue;

		printf("%s ", dent->d_name);
	}

	printf("\n\n");
		
	rewinddir(dp);

	printf(" -- if file is a directory -- \n\n");

	while ((dent = readdir(dp))) {
		if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)
			continue;

		struct stat buf;

		stat(dent->d_name, &buf);

		if (buf.st_mode & S_IFDIR) {
			printf("this file is a folder -- %s\n\n", dent->d_name);

			char* before = malloc(strlen(nameString) + 4);
			strcpy(before, nameString);
			strcat(nameString, "/");
			ls(dent->d_name, nameString);
			strcpy(nameString, before);
		}
		else {
			printf("this file is NOT a folder -- %s\n\n", dent->d_name);
		}
	}

	printf("-- directory find end -- \n\n");

	closedir(dp);
}

int main(int argc, char* argv[]) {
	char* fn = ".";
	char* nameString = malloc(sizeof(char) * 1000);
	strcpy(nameString, "");
	ls(fn, nameString);


	free(nameString);
	return 0;
}