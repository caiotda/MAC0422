#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int MAXLINE = 1024;
char prompt[] = ">> ";



int main (int argc, char **argv) {
	char* cmdline = malloc(sizeof(char) * MAXLINE);
	char path[256];
	char command[64];
	int i, j, has_found_space;

	while(1) {
		printf("%s", prompt);

		cmdline = fgets(cmdline, MAXLINE, stdin);
		for (i = 0, has_found_space = 0, j = 0; cmdline[i] != '\n'; i++) {
			if (cmdline[i] == ' ') {
				command[i] = '\0';
				has_found_space = 1;
				i++;
			}
			if (!has_found_space)
				command[i] = cmdline[i];
			else {
				path[j] = cmdline[i];
				j++;
			}
		}

		path[j] = '\0';
		printf("Seu comando foi %s\n", command);
		printf("E o caminho dado foi %s\n", path);

		if((cmdline == NULL) && ferror(stdin))
			printf("Erro no fgets");

		if(strcmp(cmdline, "end\n") == 0) {
			printf("acabou! \n");
			exit(0);
		}
	}

	return 0;
}

