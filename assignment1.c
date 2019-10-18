#include <iostream>
#include <cstring>
#include <string>
#include <sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
//#define buf 0
//#define buf_size 100
#include <sys/stat.h>
//#include <ncurses.h>

using namespace std;

char exitSmallString[]  = "exit";
char  exitBigString[] = "Exit";

int main (int argc, char *argv [ ] ) {
//clrscr();
//cls( GetStdHandle( STD_OUTPUT_HANDLE ));
printf("\e[1;1H\e[2J");
cout << "version 1.0\n";
cout << "\nBhargav's Shell Running\n"<< endl;
for(;;){
while ( true ) {




	string input = "";     
	char * cinput = NULL;  
        char* savedTokens[256] = {NULL}; 
        int nTokens = 0;   

    cout << "command me>> ";
	int len;
    getline (cin, input);
	if(input.length()<1)	
	//if (cin.get()== '\n')
	{break;
		}

    cinput = new char [input.size()+1];
    strcpy (cinput, input.c_str());    


    char* tokens = strtok (cinput," ");


         while (tokens != NULL ) {
			savedTokens[nTokens] = strdup(tokens);  
	                nTokens++;
                        tokens = strtok(NULL," ");
                                 } 
           
           if(strcmp(exitSmallString, savedTokens[0]) == 0 || strcmp(exitBigString, savedTokens[0]) == 0){
           cout << "See you later !!! exiting The Shell \n thank you\n" << endl;
           return 0;
           }
 
          // Just for the sake of testing, let's print out the tokens
         //  for(int i = 0; i < nTokens; i++){
           //cout << "savedTokens[ " << i << " ] = " << savedTokens[i] << endl;
		else if(strcmp("mkdir",savedTokens[0])==0)
		{
		int statu;
		if((statu=mkdir(savedTokens[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))==-1)
		{ 
			perror("mkdir error");
		}
		break;
		
		}
		if(strcmp("help",savedTokens[0])==0)
		{
			cout<<"The integrated commands are :\n1)cat\n2)ls -l\n3)mkdir\n4)pwd\n5)time\n6)touch\n7)remove\n8)who\n9)copy\n";
			
		}
	else if(strcmp("cat",savedTokens[0])==0)
	{
	int fd1,size;
	char buf[1000];
	   for(int i=1; i< nTokens; i++)
		{if((fd1=open(savedTokens[i],O_RDWR))==-1)
		{
			perror("error");
		}
		size=read(fd1,&buf,100000);
		cout<<buf;
		}
		
    	}
	else if(strcmp("time",savedTokens[0])==0)
	{
		time_t t;
    		time(&t);
    		printf("Today's date and time : %s",ctime(&t));
	}
	else if(strcmp("touch",savedTokens[0])==0)
	{
		int fp;
		
		for(int i=1; i< nTokens; i++)
		{
		fp=open(savedTokens[i],O_CREAT|O_RDWR|O_EXCL,0755);
		if(fp==-1)
		{
			perror("can't open file");
			exit(0);
		}
		}
	}
	else if(strcmp("remove",savedTokens[0])==0)
	{
		int status;
		status = remove(savedTokens[1]);
    
	    if( status == 0 )
		{
	        	printf("%s file deleted successfully.\n",savedTokens[1]);
		}
    		else
    		{
        		printf("Unable to delete the file\n");
        		perror("Error");
    		}


	}
	else if(strcmp("who",savedTokens[0])==0)
	{
		 char *p=getenv("USER");
	    if(p==NULL) return EXIT_FAILURE;
    		printf("%s\n",p);
    
	}
	else if(strcmp("copy",savedTokens[0])==0)
	{
		/*int fpr,fpw;
		int total_size=0;
		ssize_t nbyte_read,nbyte_write;
		char buf[buf_size];


		fpr=open(savedTokens[1],O_RDONLY);
		if(fpr<0)
		{
			perror("FAILED TO OPEN SOURCE FILE");
			
		}
		fpw=creat(savedTokens[1],S_IRWXU);
		if(fpw<0)
		{
			perror("FAILED TO OPEN DESTINATION FILE");
			exit(0);
		}
		do{

		nbyte_read=read(fpr,buf,buf_size);
		if(nbyte_read<0)
		{
			perror("FAILED TO READ FROM FILE");
			exit(0);
		}
		nbyte_write=write(fpw,buf,nbyte_read);
		if(nbyte_write<0)
		{
		perror("FAILED TO WRITE TO FILE");
		exit(0);
		}
		}while(nbyte_read>0);
		close(fpr);
		close(fpw);
*/

	}
	
	else if(strcmp("pwd",savedTokens[0])==0)
	{
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        puts("Path info by use getcwd():");
        printf("\tWorkdir: %s\n", cwd);
    	}
	
	
	else if((strcmp("ls",savedTokens[0])==0))
	{
		int yp=-1;
		
		yp=(strcmp("-l",savedTokens[1]));
	 	if(yp==0)
		{
		
		
   		 DIR *thedirectory;
    		struct dirent *thefile;
   		 struct stat thestat;
		char cwd[512];
		int c ;
    		getcwd(cwd, sizeof(cwd));
    		thedirectory = opendir(cwd);




    		while((thefile = readdir(thedirectory)) != NULL)
    		{        stat(thefile->d_name,&thestat);
            		switch (thestat.st_mode & S_IFMT) 
		{
     		       case S_IFBLK:  printf("b "); break;
     		       case S_IFCHR:  printf("c "); break; 
     		       case S_IFDIR:  printf("d"); break; //It's a (sub)directory
     		       case S_IFIFO:  printf("p "); break; //fifo
     		       case S_IFLNK:  printf("l "); break; //Sym link
     		       case S_IFSOCK: printf("s "); break;
     		       default:       printf("- "); break;
                }
     			   printf( (thestat.st_mode & S_IRUSR) ? " r" : " -");
     			   printf( (thestat.st_mode & S_IWUSR) ? "w" : "-");
     			   printf( (thestat.st_mode & S_IXUSR) ? "x" : "-");
     			   printf( (thestat.st_mode & S_IRGRP) ? "r" : "-");
        		   printf( (thestat.st_mode & S_IWGRP) ? "w" : "-");
       			   printf( (thestat.st_mode & S_IXGRP) ? "x" : "-");
        		   printf( (thestat.st_mode & S_IROTH) ? "r" : "-");
                	   printf( (thestat.st_mode & S_IWOTH) ? "w" : "-");
        		   printf( (thestat.st_mode & S_IXOTH) ? "x" : "-");
        		   printf("\t%d ", thestat.st_nlink);
        		   printf("%u\t",thestat.st_uid);
                	   printf("%lld\t",thestat.st_size);
        		   printf(" %s", thefile->d_name);
        		   printf(" %s", ctime(&thestat.st_mtime));
    		}
    			closedir(thedirectory);
			

 
		}
		else if(yp==-1)
		{
			DIR *tedirectory;
	   		struct dirent *thfile;
    			struct stat thstat;
			char cw[512];
			int c ;
    			getcwd(cw, sizeof(cw));
    			tedirectory = opendir(cw);
			while((thfile = readdir(tedirectory)) != NULL)
    			{   
	      		        stat(thfile->d_name,&thstat);
				printf(" %s\n", thfile->d_name);
	        	}	
	        	closedir(tedirectory);
	
		}
	}
	//else if(strcmp("ls",savedTokens[0])==0)
	//{    
				

	//}

     	else 
	{
		system(input.c_str());
	}
    }}
return 0;
}
