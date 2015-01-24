#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

#define delim " \n\t\r\""

int main ()
{
	char hostname[256];
	char login[256];

	// getting login and hostname, error checking	
	int loginerr = getlogin_r(login, sizeof(login)-1);
	int hosterr = gethostname(hostname, sizeof(hostname)-1);
	if(loginerr == -1)
		perror("getlogin");
	if(hosterr == -1)
		perror("hostname");

	//array for input	
	char input[256];
	char *arg[512];
	char *par1 = NULL; //first parse
	
	while(1)
	{

//start:		//retrieves input	
		cout << login << "@" << hostname << "$ " ;
		fgets(input, 256, stdin);	
		par1 = strtok(input, delim);
		
		
		//if(par1[0] == '\0')
		//	goto start;

		for(int i = 0; i < 255; ++i)
		{
			if(input[i] == '#')
			{
				input[i] = '\0';
				break;
			}

			//else if(input[i] == ';')
			//{
				
			//}
		}
	
		if(strcmp(par1, "exit") == 0)
			exit(0);
	
		int fid = fork(); // for pid
		
		if(fid == 0)
		{
			
			arg[0] = new char[256];
			strcpy(arg[0], par1); //command into arg 

			par1 = strtok(NULL, delim);
			unsigned i = 1;
			while(par1 != NULL)
			{	
				arg[i] = new char[256];
				strcpy(arg[i] ,par1);
				par1 = strtok(NULL, delim);
				++i;	
			}
				int eid = execvp(arg[0], arg);
				if(eid != 0)
				{
					perror("execvp");
					exit(0);
				}
			
		}

		else if(fid == -1)
		{
			perror("fork");
			exit(0);
		}
		
		else
		{
			if(wait(NULL)==-1)
				perror("wait");
		}	
	}


	cout << endl;

	return 0;
}
