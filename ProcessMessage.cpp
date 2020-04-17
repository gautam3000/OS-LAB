#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
int32_t main()
{
    int fd[2];
	char *str;

	// create pipe
	pipe(fd);

	// fork() returns 0 for child process, child-pid for parent process.
    pid_t p;
    p = fork();
    switch(p){
        
        case -1:
            printf("Error\n");
            break;

        case 0:
            // child process
            //closing the write descriptor
		    close(fd[1]);

		    read(fd[0], &str, 19);
		    printf("Child ID = %d, Received Message =  %s\n", getpid(), str);
            printf("Message received successfully!\n\n");
		    // closeing the read descriptor
		    close(fd[0]);
            break;

        default:
             // parent process
		    close(fd[0]);

		    // send the string to the child process
		    str = "end term practical"; 
		    write(fd[1], &str, 19);
		    printf("Parent ID = %d, Send Message = %s\n", getpid(), str);
            printf("Message sent successfully!\n\n");
            close(fd[1]);
    }
    
    return 0;
}
