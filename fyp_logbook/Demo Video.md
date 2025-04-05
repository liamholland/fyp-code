# Part Zero: Intro
[shot of laptop and mic on the ground with Galway city as the background]

[i walk up the hill into the shot]

"i am on the top of a hill in Galway and it was in this city that I worked on and completed the project that you are about to see"

"before I demo the project, I am going to provide some context for what its all about at a high level. we will get into more detail later."

[take out the piece of paper from my back pocket]

"i think you can for the most part see this. its pretty windy out here out here so i didn't want to bring out the big chart."

[pause for a moment]

"actually im a computer guy im sure i can figure something out"

[diagrams drawn in paint can be placed on the shot]

# Part One: Context
do a pirate software style introduction to the following:

graphs

graph colouring

distributed graph colouring

The representation of a graph in the code

# Part Two: Code
Show and explain the following parts of the code:

The node representation for real
- Explain each field
- Mention the size in bytes
- Discuss the trade-off against the adjacency list or matrix

The way the kernels integrate into the program
- Show the kernel file
- Point out how inputs are immutable
- Show how the kernels are called

Dynamic parts of the code
- Explain at a high level from the graphcolourer function how dynamic kernels are called
- Jump to the graphutil functions and explain some of the context around why i chose to make these edit the input parameters
- Show the dynamic kernels and how simple they are to create

The testing framework
- Show the make file command and main function
- Show the unit tests
- Show how the tests are collected
- Compile and run the tests


# Part Three: Demo
Simply demo each of the experiments from the github i think

**colour a ring graph with 51 nodes and 10000 iterations max**
```sh
./colouring.exe -n 51 -g o -M 10000
```
**colour a random graph which has a probability of 30% that each edge exists**
```sh
./colouring.exe -p 0.3
```
**colour a bipartite graph with 2 nodes in the first set and 4 in the second**
```sh
./colouring.exe -g b -n 6 -s 2
```
**colour a connected random graph with 1001 nodes, using at least 5 colours and at most 50 colours**
```sh
./colouring.exe -n 1001 -p 1 -c 5 -C 50
```
**colour a random graph with 300 nodes and 70% probability for each edge, using 50 agents that move twice on each turn, save the results and run it on 10 different graphs**
```sh
./colouring.exe -n 300 -p 0.7 -a 50 -m 2 -A 10 -S
```
**colour a random graph using the configuration of the decrementing kernel for colouring and the node removal kernel as a dynamic aspect, then view the graph in the interactive mode when finished**
```sh
./colouring.exe -n 100 -p 0.5 -K dnx -v
```


# Part Four: Expansion
add to the code

add a kernel to the code which allows the agents to identify the node with the highest degree

this will involve:
- adding a read out of the id of the highest degree node to the screen
- adding a field to the node struct "chosen"
	- a boolean value
- adding a kernel which takes in an agent and identifies the neighbour it believes to be the highest degree node by picking out the highest colour in its locality
	- max of the colour vector
- adding an option for it to the main function
- running the experiment and seeing if it works

would expect this to be harder for lower density graphs and easier for higher ones


#fyp 



