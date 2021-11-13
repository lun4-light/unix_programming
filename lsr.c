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
	struct stat buf;

	if ((dp = opendir(fileName)) == NULL) {
		perror("opendir");
		exit(1);
	}

	strcat(nameString, fileName);

	printf("%s:\n\n", nameString);

	while ((dent = readdir(dp))) {
		if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)
			continue;

		printf("%s ", dent->d_name);
	}

	printf("\n\n");
		
	rewinddir(dp);

	while ((dent = readdir(dp))) {
		if (strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)
			continue;

		stat(dent->d_name, &buf);

		if (buf.st_mode & S_IFDIR) {
			char* before = nameString;
			strcat(nameString, "/");
			ls(dent->d_name, nameString);
			strcpy(nameString, before);
		}
	}

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