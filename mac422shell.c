#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int MAXLINE = 1024;
char prompt[] = ">> ";

char **get_input(char *input) {
    char **command = malloc(16 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}

int main (int argc, char **argv) {
	char* cmdline = malloc(sizeof(char) * MAXLINE);
	char** args = malloc(sizeof(char *) * 8);
	char** cmd;
	int i, status, exec_stat, fd;

	while(1) {
		printf("%s", prompt);		

		cmdline = fgets(cmdline, MAXLINE, stdin);
		if(strlen(cmdline) == 1) {
			continue;
		}
		cmdline = strtok(cmdline, "\n");
		cmd = get_input(cmdline);

		for(i = 0; cmd[i] != NULL; i++) {
			args[i] = cmd[i+1];
		}

		if (strcmp(cmd[0], "protegepracaramba") == 0) {
			if (fork() != 0) { /* Processo pai */
				waitpid(-1, &status, 0);
			}
			else { /* Processo filho */
				chmod(args[0], 0000);
				exit(0);
			}
		}
		else if (strcmp(cmd[0], "liberageral") == 0) {
			if (fork() != 0) { /* Processo pai */
				waitpid(-1, &status, 0);
			}
			else { /* Processo filho */
				chmod(args[0], 0777);
			}
		}
		else if (strcmp(cmd[0], "rodeveja") == 0) {
			if (fork() != 0) { /* Processo pai */
				waitpid(-1, &status, 0);
				printf("Programa %s retornou código %d\n", args[0], status);
			}
			else { /* Processo filho */
				exec_stat = execve(args[0], args, 0);
				exit(exec_stat); 
			}
		}
		else if (strcmp(cmd[0], "rode") == 0) {
			if (fork() != 0) {
				signal(SIGCHLD, SIG_IGN);
			}
			else {
				/* Processo filho */
				close(STDERR_FILENO);
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				fd = open("/dev/null", O_RDWR);
				dup(fd);
				dup(fd);
				exec_stat = execve(args[0], args, 0);
				exit(exec_stat); 
			}
		}

		else {
			printf("Comando não reconhecido\n");
		}


		if((cmdline == NULL) && ferror(stdin))
			printf("Erro no fgets\n");
	}

	return 0;
}
