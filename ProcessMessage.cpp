#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
int main()
{
	int fd[2];
	char *whd;

	// create pipe
	pipe(fd);

	// fork() returns 0 for child process, child-pid for parent process.
	pid_t q;
	q = fork();
	switch (q)
	{

	case 0:
		// child process
		//closing the write descriptor
		close(fd[1]);

		read(fd[0], &whd, 19);
		printf("Child ID = %d, Received Message =  %s\n", getpid(), whd);
		printf("Message send!\n\n");
		// closeing the read descriptor
		close(fd[0]);
		break;

	default:
		// parent process
		close(fd[0]);

		// send the string to the child process
		whd = "ETE prtical";
		write(fd[1], &whd, 19);
		printf("Parent ID = %d, Send Message = %s\n", getpid(), whd);
		printf("Message send!\n\n");
		close(fd[1]);
	}

	return 0;
}
