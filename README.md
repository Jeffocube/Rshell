# CS 100 Programming Project
W2019 
Kevin Lee 861170626
Jeffery Lai 862043827

# Introduction:
The program we are creating will be a shell called RShell. It will have some of the capabilities of the current shell we use, bash. This includes printing a command prompt, taking in user input, and translating those commands into services that the user requests. For this assignment, we will use the Composite Pattern as our framework for the program. This is important as the user will be entering different inputs and the having a composite pattern will allow the user to treat all the objects in the program in the same manner.
# Diagram:

# Classes:
Our classes will be derived from an interface that we will call "Input"
Input will be similar to the interface for the second lab
The connector class will be a composite class. This class will be similar to the operator class from the third lab. It will be a binary operator which will have pointers to two input classes.
The command class will be a leaf class that will run an executable with the operands that are given by execvp()
# Prototypes/Research:

# Developing and Testing Roadmap:
