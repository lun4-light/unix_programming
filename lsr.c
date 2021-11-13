#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ls(char* fileName) {
	DIR* dp;
	struct dirent* dent;

	if ((dp = opendir(fileName)) == NULL) {
		perror("opendir");
		exit(1);
	}

	printf("%s:\n\n", fileName);

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
			ls(dent->d_name);
		}

	}

	closedir(dp);
}

int main(int argc, char* argv[]) {
	char* fn = ".";
	ls(fn);

	return 0;
}