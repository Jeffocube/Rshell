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
Note: The execvp() function takes in a char* const* variable
# Developing and Testing Roadmap:

