#include "pipe.h"

extern int exec_cmd_main(char **cmd, char **envp);
int main(int argc, char **argv, char **envp)
{
	char *test[100];

	test[0] = strdup("ls");
	test[1] = strdup(">a");
	test[2] = strdup("|");
	test[3] = strdup("cat");
	test[4] = strdup(">d");
	test[5] = NULL;
	exec_cmd_main(test, envp);
	return (argc);
}
