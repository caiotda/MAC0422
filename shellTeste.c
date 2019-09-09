#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int MAXLINE = 1024;
char prompt[] = ">> ";



int main (int argc, char **argv) {
	char* cmdline = malloc(sizeof(char) * MAXLINE);

	while(1) {
		printf("%s", prompt);

		cmdline = fgets(cmdline, MAXLINE, stdin);
		printf("Voce digitou : %s\n", cmdline);		
		if((cmdline == NULL) && ferror(stdin))
			printf("Erro no fgets");

		if(strcmp(cmdline, "end\n") == 0) {
			printf("acabou! \n");
			exit(0);
		}
	}

	return 0;
}

