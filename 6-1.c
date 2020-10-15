#include <stdio.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s [dir]", argv[1]);
		return 1;
	}
	DIR *dir_str = opendir(argv[1]);
	if (dir_str == NULL)
	{
		perror("Failed to opendir");
		return 2;
	}
 	struct dirent *dir;

	while ((dir = readdir(dir_str)) != NULL){
		printf("%s\n", dir->d_name);
	}
		
	closedir(dir_str);
	return 1;
}
