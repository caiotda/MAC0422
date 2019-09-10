#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int MAXLINE = 1024;
char prompt[] = ">> ";

// -r-xr-xr-x

int main (int argc, char **argv) {
	char* cmdline = malloc(sizeof(char) * MAXLINE);
	char path[256];
	char command[64];
	int i, j, has_found_space, status;
	char* default_commands[4];
	FILE* fd;

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

		if(strcmp(cmdline, "end\n") == 0) {
			printf("acabou! \n");
			exit(0);
		}

		if (strcmp(command, "protegepracaramba") == 0) {
			if (fork() != 0) { /* papai */
				waitpid(-1, &status, 0);
			}
			else { /* nao eh o papai */
				chmod(path, 0000);
			}
		}
		else if (strcmp(command, "liberageral") == 0) {
			if (fork() != 0) { /* papai */
				waitpid(-1, &status, 0);
			}
			else { /* nao eh o papai */
				chmod(path, 0777);
			}
		}
		else if (strcmp(command, "rodeveja") == 0) {
			printf("olha para meu popozao");
		}
		else if (strcmp(command, "rode") == 0) {
			printf("a bolsinha");
		}
		else {
			printf("digita algo certo seu burro");
		}


		if((cmdline == NULL) && ferror(stdin))
			printf("Erro no fgets");

	}

	return 0;
}

