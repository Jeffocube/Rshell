# CS 100 Programming Project
W2019 
Kevin Lee 861170626
Jeffery Lai 862043827

# Introduction:
The program we are creating will be a shell called RShell. It will have some of the capabilities of the current shell we use, bash. This includes printing a command prompt, taking in user input, and translating those commands into services that the user requests. For this assignment, we will use the Composite Pattern as our framework for the program. This is important as the user will be entering different inputs and the having a composite pattern will allow the user to treat all the objects in the program in the same manner.
# Diagram:

![UML](https://github.com/cs100/assignment-cs100_jeffery_and_kevin/blob/master/images/UML%20Shell%20(1).jpeg)
# Classes:
Our classes will be derived from an interface that we will call "Input"

Input:

    will act as the interface similar to the lab examples. Contains Commands and the Execution of those commands. Below are classes that derive from the Input class.

Commands:

    We will have two command classes. The first is a composite called commandComp, this will encompass all other commands/inputs and will contain a vector that contains all these inputs. The second is commandLeaf which will contain the actual commands themself. When execute is called on commandComp, it will call execute on the commandLeaf and commandLeaf will execute a command such as "echo hello world". commandLeaf contains a string to the command called "activity" and a vector of arguments.

Connector:

    The connector will be a special object that will influence the iterator used to run through the vector of the commandLeaf. This is done by taking in the commandComp object of which is the parent to the connector and the iterator pointer and then changing the iterator depending on how the last command went.

Exit:

    The exit object will run the exit call to leave the program when executed.
# Prototypes/Research:

Running a basic program to examine the behavior of fork(),
```
    pid_t testpid = fork();

        cout << "testpid = " << testpid << endl;
```
we get the output:
testpid = 38811
0
38812
0

note: declaring a variable =fork() will result in an instance of fork running.

After the first cout line I decided to test adding  `cout << "testing raw fork" << fork() << endl;`
which was interesting because it returned: 

testpid = 38876
testing raw fork
testpid = 0
38877
testing raw fork
0
38878
0

So fork appears to create branches within branches of another process? Every 0 is a signal that the program successfully forked from the parent processes, which denotes the end of the process tree. Another note, the parent process IDs (non 0's) appear to iterate +1 every new process. In total from 2 cout fork calls, we get 6 calls to cout: original parent + 2 calls of the other fork() + child's version of the 2 other calls.	


Prototype with the 3 functions together:

```
nclude <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main(int argc, char** argv){

      //fork prototype

    int status;
      pid_t testpid = fork();
      cout << "pid_t = testpid = fork();" << endl;


    execvp(argv[1] , argv + 1);
    cout << "execvp argv[1] argv + 1;" << endl;


    waitpid(testpid, &status, 0);
        cout << "waitpid created with testpid " << endl;

      //cout << "testpid = " << testpid << endl;

      //cout << "testing raw fork" << endl;

      //cout << fork() << endl;
    //execvp prototype
    execvp(argv[1] , argv + 1);
        cout << "execvp argc1, argv + 1; " << endl;


        if (testpid == -1)
        {
                cout << "-1 error" << endl;
        }
        if (testpid == 0)
        {
                cout << "0, successfully forked back " << endl;
        }
        if (testpid > 0)
        {
                cout << "child process starts" << endl;
        }


    return 0;
}
```

Note: when entering 2 noncommand arguments when running ./a.out, more process instances are ran through the forks. When entering "echo hello", the program echoes hello twice after announcing "testpid was initialized" echoes twice, but program ends after the first execvp statement.


Note: The execvp() function takes in a char* const* variable
Note: When using parentheses, if any of the commands run, the total command will be true. 
Note: We should use a commandComp for the parentheses and add a bool into the commandComp which will allow the commandComp to act like a child.

Prototyping stat function:

After making a very simple program that uses the stat function to take a look at a test file (txt with 3 random lines), we see that we need to declare a stat variable, use the stat(const char*, stat*) function to assign a file to the stat object, and then we can simply print information such as statvariabe.st_size (the size in bits) or statvariable.st_atime (last time the file was accessed).
Here is the simple block of code:
```
int main()
{
    struct stat test;
    
    stat("texttest.txt", &test);
    
    cout << "st_size = %o\n" << test.st_size << endl;
    cout << "st_atime = %o\n" << test.st_atime << endl;
    return 0;
}
```

We can also use a switch statement in order to use the S_IF macros in a block of code such as 
```
switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }
```
Which is similar to a big if else if block. Using this, we can easily select a file and print its file type.

For our program, we can adapt usage of the switch statement and S_IFDIR and S_IFREG to treat directories and regular files accordingly.


In order to dynamically select the target file, we use parameters when running the test program 
```
int main(int argc, char *argv[])
```
and now we can run ./a.out <pathname> to select the file. 
This is a possible format we can use to implement our use of the stat functions.

In an example given in the specs:
```
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    struct stat sb;

   if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

   if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

   printf("File type:                ");

   switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }

   printf("I-node number:            %ld\n", (long) sb.st_ino);

   printf("Mode:                     %lo (octal)\n",
            (unsigned long) sb.st_mode);

   printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
            (long) sb.st_uid, (long) sb.st_gid);

   printf("Preferred I/O block size: %ld bytes\n",
            (long) sb.st_blksize);
    printf("File size:                %lld bytes\n",
            (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n",
            (long long) sb.st_blocks);

   printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));

   exit(EXIT_SUCCESS);
}
```
We can see by the output 
```
$ ./a.out texttest.txt
File type:                regular file
I-node number:            846
Mode:                     100644 (octal)
Link count:               1
Ownership:                UID=1000   GID=1000
Preferred I/O block size: 4096 bytes
File size:                32 bytes
Blocks allocated:         8
Last status change:       Wed Feb 27 18:52:51 2019
Last file access:         Wed Feb 27 18:35:57 2019
Last file modification:   Wed Feb 27 18:52:51 2019
```
how extensive we can make a file status program, adding as few or many items of information to check.

Prototyping dup and pipe :

dup/dup2 -> creates a copy of a given file descriptor (fd)
pipe -> acts as a queue data structure FIFO

```
#include <stdio.h> 
#include <unistd.h> 
#define MSGSIZE 16 
char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 
  
int main() 
{ 
    char inbuf[MSGSIZE]; 
    int p[2], i; 
  
    if (pipe(p) < 0) 
        exit(1); 
  
    /* continued */
    /* write pipe */
  
    write(p[1], msg1, MSGSIZE); 
    write(p[1], msg2, MSGSIZE); 
    write(p[1], msg3, MSGSIZE); 
  
    for (i = 0; i < 3; i++) { 
        /* read pipe */
        read(p[0], inbuf, MSGSIZE); 
        printf("% s\n", inbuf); 
    } 
    return 0; 
} 
```
This block of code is an example of using pipe to output a queue of strings.

```
int main() 
{ 
    // open() returns a file descriptor file_desc to a  
    // the file "dup.txt" here" 
  
    int file_desc = open("dup.txt", O_WRONLY | O_APPEND); 
      
    if(file_desc < 0) 
        printf("Error opening the file\n"); 
      
    // dup() will create the copy of file_desc as the copy_desc 
    // then both can be used interchangeably. 
  
    int copy_desc = dup(file_desc); 
          
    // write() will write the given string into the file 
    // referred by the file descriptors 
  
    write(copy_desc,"This will be output to the file named dup.txt\n", 46); 
          
    write(file_desc,"This will also be output to the file named dup.txt\n", 51); 
      
    return 0; 
} 
```
This block of code for dup shows how it is essentially used. Notice the two fd's can be used interchangeably.
```
// CPP program to illustrate dup2()  
#include<stdlib.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<fcntl.h> 
  
int main() 
{ 
    int file_desc = open("tricky.txt",O_WRONLY | O_APPEND); 
      
    // here the newfd is the file descriptor of stdout (i.e. 1) 
    dup2(file_desc, 1) ;  
          
    // All the printf statements will be written in the file 
    // "tricky.txt" 
    printf("I will be printed in the file tricky.txt\n"); 
      
return 0; 
} 
```
The dup2() system call is similar to dup() but the basic difference between them is that instead of using the lowest-numbered unused file descriptor, it uses the descriptor number specified by the user.

# Developing and Testing Roadmap:

Steps:

Check KanBan for updated Issues

Start discussing the piping

Experiment with the symbols in bash

Prototype test piping

Clean up some code if possible #14

Assignments subject to change	


[KanBan](https://github.com/cs100/assignment-cs100_jeffery_and_kevin/projects/1)












