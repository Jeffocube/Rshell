# CS 100 Programming Project
W2019 
Kevin Lee 861170626
Jeffery Lai 862043827

# Introduction:
The program we are creating will be a shell called RShell. It will have some of the capabilities of the current shell we use, bash. This includes printing a command prompt, taking in user input, and translating those commands into services that the user requests. For this assignment, we will use the Composite Pattern as our framework for the program. This is important as the user will be entering different inputs and the having a composite pattern will allow the user to treat all the objects in the program in the same manner.
# Diagram:
//insert image url
# Classes:
Our classes will be derived from an interface that we will call "Input"
Input
    will act as the interface similar to the lab examples. Contains Command and the Execution of those commands.

Command 
    COMPOSITE class. Used as a base for all the possible commands that will be executed.
The connector will be a flag placed in composite class. It will function similarly to the operator classes from the composite pattern lab in the way that it is passed as a parameter that decides if another Command object will execute, similar to if a Base type object was passed in as a paramter in the operator class from the lab.

Execute
    When all Command objects are done being made, the execute class will carry out the commands following the connectors. 
# Prototypes/Research:
When running a basic program to examine the behavior of fork(),
```
    pid_t testpid = fork();

        cout << "testpid = " << testpid << endl;
```
we get the output:
testpid = 38811

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

So fork appears to create branches within branches of another process? Every 0 is a signal that the program successfully forked from the parent processes, which denotes the end of the process tree. Another note, the parent process IDs (non 0's) appear to iterate +1 every new process. In total from 2 cout fork calls, we get 6 calls to cout: original parent + 2 calls of the other fork() + child's version of the 2 other calls


Adding more functionality: using execvp to run commands




# Developing and Testing Roadmap:

