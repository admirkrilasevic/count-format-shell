#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void executeCommand(char **argv){
	int rc = fork();                        //using fork() system call to create a child process

	if (rc < 0){                            //if fork failed
		printf("Error: Fork failed\n");
		exit(1);
	}
	else if (rc == 0){                      //child process:
		if (execvp(*argv, argv) < 0){   //using execvp to execute command
			printf("Error: Command execution failed\n");
			exit(1);
		}
	}
	else{                                   //parent process:
		int rc_wait = wait(NULL);       //using wait() so parent waits for child process completion
	}
}

void countCharacters(char **argv){
         argv[0] = strdup("wc");       //unix command wc used to count words, characters and lines
       	 argv[1] = strdup("-c");       //flag -c used to only return number of characters
         printf("Enter the file name: ");
       	 char file[1024];
       	 gets(file);
       	 argv[2] = strdup(file);       
       	 argv[3] = NULL;               //NULL used to denote the end of arguments
	 executeCommand(argv);                  
}

void countWords(char **argv){
	argv[0] = strdup("wc");     
	argv[1] = strdup("-w");       //flag -w used to only return the number of words
	printf("Enter the file name: ");
	char file[1024];
	gets(file);
	argv[2] = strdup(file);
	argv[3] = NULL;
	executeCommand(argv);         
}

void countLines(char **argv){
	argv[0] = strdup("wc");
       	argv[1] = strdup("-l");       //flag -l used to only return the number of lines
       	printf("Enter the file name: ");
       	char file[1024];
       	gets(file);
        argv[2] = strdup(file);       
        argv[3] = NULL;
	executeCommand(argv);         
}

void countOccurence(char **argv){
         argv[0] = strdup("grep");       //unix command grep used to search for occurences of words/characters 
	 argv[1] = strdup("-ic");         //flag -c used to return the count of occurences, flag -i used to ignore the case
         printf("Enter the file name: ");
       	 char file[1024];
       	 gets(file);
	 printf("Enter the word/character: ");
	 char string[64];
	 gets(string);
	 argv[2] = strdup(string);
       	 argv[3] = strdup(file);       
       	 argv[4] = NULL;
	 executeCommand(argv);
}

void formatLowercase(char **argv){
        printf("Enter the file name: ");
        char file[1024];
        gets(file);

        FILE *fptr;                      //file pointer created
        fptr = fopen(file, "r");         //file opened
        
        if (fptr == NULL) {              //if error occured while opening, show error
                printf("Error occured while opening file\n");
                exit(1);
        }
        
        int c;
        while((c = getc(fptr)) != EOF){  //read characters from file until end of file (EOF)
                putchar(tolower(c));     //convert to lowercase
        }
        fclose(fptr);                    //file closed

}

void formatUppercase(){                     
        printf("Enter the file name: ");
        char file[1024];
        gets(file);

        FILE *fptr;                 
        fptr = fopen(file, "r");
        
        if (fptr == NULL) {
                printf("Error occurred while opening file\n");
                exit(1);
        }
                
        int c;
        while((c = getc(fptr)) != EOF){
                putchar(toupper(c));    //convert to uppercase
        }
        fclose(fptr);
}

void formatCamel(char **argv){
	printf("Enter the file name: ");
	char file[1024];
	gets(file);

	FILE *fptr;
	fptr = fopen(file, "r");

	if (fptr == NULL){
		printf("Error occured while openning file\n");
		exit(1);
	}
	
	char str[1024];
	int i, count = 0;
	while (fgets(str, 1024, fptr) != NULL){              //reading string from file
		for(int j=0; str[j]!='\0'; j++){             //using a for loop to change the case and remove whitespace
		if(j==0){
			if((str[j]>='a' && str[j]<='z'))
				str[j]=str[j]-32;
			continue;
		}
		if(str[j]==' '){
			++j;
			if(str[j]>='a' && str[j]<='z'){
				str[j]=str[j]-32;
				continue;
			}
		}
		else{
			if(str[j]>='A' && str[j]<='Z')
				str[j]=str[j]+32;
		}
		}
	}

   for(i = 0; str[i]; i++){      //loop used to count characters in the string, to later mark the end of it
       if(str[i] != ' '){
           str[count] = str[i];
           count++;
       }
   }
   str[count]='\0';

   printf("%s",str);



}

void main(){
	char line[1024];                           //for storing user input
	char *argv[64];                            //for storing arguments for execution

	while (1){                                 //infinite loop
		printf("\nCommands available:\n");
		printf("countCharacters - count how any characters are in a file\n");
		printf("countWords - count how many words are in a file\n");
		printf("countLines - count how many lines are in a file\n");
		printf("countOccurence - count occurence of a character or a word in a file\n");
		printf("formatCamel - format text in a camel case manner\n");
		printf("formatLowercase - convert text to lowercase\n");
		printf("formatUppercase - convert text to uppercase\n");
		printf("exit - terminate the shell\n");
		printf("Enter the name of the command you wish to execute below:\n");
		printf("Shell -> ");
		gets(line);                        //take user input from command line
		printf("\n");
		if (strcmp(line, "countCharacters") == 0) 
			countCharacters(argv);
		else if (strcmp(line, "countWords") == 0)
			countWords(argv);
		else if (strcmp(line, "countLines") == 0)
			countLines(argv);
		else if (strcmp(line, "countOccurence") == 0)
			countOccurence(argv);
		else if (strcmp(line, "formatCamel") == 0)
			formatCamel(argv); 
		else if (strcmp(line, "formatLowercase") == 0)
			formatLowercase(argv);
		else if (strcmp(line, "formatUppercase") == 0)
			formatUppercase();          
		else if (strcmp(line, "exit") == 0)  //if the entered command is exit, exit
			exit(0);
		else
			printf("Invalid command!\n");
	}
}	

