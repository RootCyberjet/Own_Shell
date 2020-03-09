/* In this program, program accepts our input as command to be executed */


#include<stdio.h>
#include<stdlib.h>		/* For exit() function */
#include<unistd.h>
#include<wait.h>		/* For wait() system call */
#include<string.h>		/* For strtok() function */

#define DELIM "\n\t\r "		/* choosing white-space delimiters */
#define buf_size 4096		

void main()
{
	int i, n;
	char buffer[buf_size];	/* Stores all command-line here */
	char *arg[100];		/* Stores all arguments from command-line */
	int exit_stat;		/* For storing exit status of child process */

	while(1)		/* For a infinite loop */
	{
		n=1;
		write(STDOUT_FILENO,"MY_SHELL >_ ",12);		/* Printing a promt in STDOUT */
		read(STDIN_FILENO, buffer, buf_size);		/* Stores buffer from STDIN */
		if(strcmp(buffer, "exit\n") == 0)		/* If input be "exit" then exit the shell */
		{
			printf("Thank you for using my_shell....\n");
			exit(0);
		}

		arg[0] = strtok(buffer,DELIM);			/* Stores first word in arg[0] */

		while((arg[n] = strtok(NULL, DELIM)) != NULL)	/* Stores next words in arg[1], arg[2] and so on... */
		{
			n++;
		}

		arg[n] = NULL;					/* Stores NULL character in last member of arg array */

		switch(fork())					/* Make a child process */
		{
			case -1:				/* If forking failed then print an error message and exit the shell */
				{
					perror("Forking error");
					exit(1);
				}
			case 0:					/* Execute command in child process */
				{
					if((execvp(arg[0], &arg[0])) == -1);
					exit(1);
				}
			default:				/* Parent process */
				{
					wait(&exit_stat);	/* After completed child process to start parent process */
					if(WEXITSTATUS(exit_stat) == 0) /* Print exit status of executed command */
					{
						printf("Exit status of command : %d (success)\n",WEXITSTATUS(exit_stat));
					}
					else
					{
						printf("Exit status of command : %d (failure)\n",WEXITSTATUS(exit_stat));
					}
					for(i=0;i<=n;i++)	/* Clear all data stored in arg array */
					{
						arg[i] = "\0";
					}
					for(i=0;i<buf_size;i++)	/* Clear all data stored in buffer array */
					{
						buffer[i] = '\0';
					}
				}
		}
	}
	exit(0);
}
