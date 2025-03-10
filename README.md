```

 ________ ___  ________   ________  ___                                  
|\  _____\\  \|\   ___  \|\   __  \|\  \                                 
\ \  \__/\ \  \ \  \\ \  \ \  \|\  \ \  \                                
 \ \   __\\ \  \ \  \\ \  \ \   __  \ \  \                               
  \ \  \_| \ \  \ \  \\ \  \ \  \ \  \ \  \____                          
   \ \__\   \ \__\ \__\\ \__\ \__\ \__\ \_______\                        
    \|__|    \|__|\|__| \|__|\|__|\|__|\|_______|                        
                                                                         
                                                                         
                                                                         
  ___    ___ _______   ________  ________                                
 |\  \  /  /|\  ___ \ |\   __  \|\   __  \                               
 \ \  \/  / | \   __/|\ \  \|\  \ \  \|\  \                              
  \ \    / / \ \  \_|/_\ \   __  \ \   _  _\                             
   \/  /  /   \ \  \_|\ \ \  \ \  \ \  \\  \|                            
 __/  / /      \ \_______\ \__\ \__\ \__\\ _\                            
|\___/ /        \|_______|\|__|\|__|\|__|\|__|                           
\|___|/                                                                  
                                                                         
                                                                         
 ________  ________  ________        ___  _______   ________ _________   
|\   __  \|\   __  \|\   __  \      |\  \|\  ___ \ |\   ____\\___   ___\ 
\ \  \|\  \ \  \|\  \ \  \|\  \     \ \  \ \   __/|\ \  \___\|___ \  \_| 
 \ \   ____\ \   _  _\ \  \\\  \  __ \ \  \ \  \_|/_\ \  \       \ \  \  
  \ \  \___|\ \  \\  \\ \  \\\  \|\  \\_\  \ \  \_|\ \ \  \____   \ \  \ 
   \ \__\    \ \__\\ _\\ \_______\ \________\ \_______\ \_______\  \ \__\
    \|__|     \|__|\|__|\|_______|\|________|\|_______|\|_______|   \|__|

```

This repository is the code for my **final year project**, dealing with **decentralised approaches to graph colouring**.

## Local Setup

- clone the repo
- run make
```
make
```
- alternatively manually compile the src files with whatever compiler you prefer

## Usage

- Run the executable you compiled from the command line with some variation of the following options
```
usage: colouring.exe [options]
options:
-h                print these instructions
-n [integer]      set the number of nodes in the graph
                    default is 10
-M [integer]      set the max iterations
                    default is 50000 (plenty)
                    this limits the amount of time the agent algorithm can run for
-c [integer]      colour lower bound
                    if you set this parameter, the algorithm will try and colour the graph
                    with that many colours
                    if it fails to find a solution, it will increment the number of colours
                    until it reaches the upper bound
-C [integer]      colour upper bound
                    the default is determined by a brute force centralised approach
                    this paramter will have no effect if the lower bound is not also set
                    can be used to ensure that the solution is optimal or to force conflicts
-S [name/path]    set the save mode on
                    flag which sets whether the results are saved to a file called results.csv
                    the default is false
                    the name/path is optional, but allows for custom names or paths if included
-A [integer]      number of automatic runs
                    default is 1 (run the program once)
                    increasing the number will run the program that number of times
                    can be used to save multiple runs of the same settings
-a [integer]      number of agents
                    sets the number of agents (active nodes) in the colouring algorithm
                    the default is an agent at every vertex
                    maximum is the number of nodes in the graph
-m [integer]      number of agent moves
                    sets the number of moves an agent makes on each "turn"
                    the default is 0 (agents are stationary)
-v                set visualise mode on
                    prints the graph when the colouring is complete
                    enters the user into an interactive traversal mode
                    can be useful to help visualise graphs
                    default is off
-g [generator]    set the generator
                    sets the graph generator function to use
                    there are currently two different types of graphs you can use
                      r: random graph; each edge has a p% chance of existing (default)
                        options:
                          -p [float]      probability (as a floating point number between 0 and 1)
                                            probability that each edge of the graph exists
                                            default is 0.5
                      o: ring graph; undirected graph where each node has two neighbours
                      b: bipartite graph; a graph of two disjoint subsets
                        options:
                          -s [integer]    set one; the number of nodes in the first subset
                                            the default is to split the number of nodes in two
-k [kernel]       set the colouring kernel
                    sets the kernel used to colour the nodes
                    options include:
                      m: local minimum (default); applies the local minimum colour
                      r: random kernel; picks a colour between 1 and max if in conflict
                      d: colour-blind decrement; decrements colour if in conflict
                      i: colour-blind increment; increments colour if in conflict
                      a: amongus kernel; introduces a bad actor (colours with m)
-d [kernel]       set the dynamic kernel
                    sets the kernel used to modify the topology of the graph
                    options include:
                      x: no dynamic kernel (default)
                      e: possibly remove edge
                      n: possibly remove node
                      o: remove orphan nodes
                      t: remove nodes based on a threshold
-w [kernel]       set the movement kernel
                    sets the kernel used to move agents between nodes
                    options include:
                      x: no movement kernel (default)
                      r: random movement kernel
                      o: optimal movement kernel
-K [config]       set kernel config
                    sets the kernel config based on the provided string
                    the string is parsed in the format [colour, dynamic, movement]
                    for example, the default configuration is 'mxx'
                    colour-blind decrement with possible edge removal would be 'dex'
```

#### Example Usage
**colour a ring graph with 51 nodes and 10000 iterations max**
```
./colouring.exe -n 51 -g o -M 10000
```
**colour a random graph which has a probability of 30% that each edge exists**
```
./colouring.exe -p 0.3
```
**colour a bipartite graph with 2 nodes in the first set and 4 in the second**
```
./colouring.exe -g b -n 6 -s 2
```
**colour a connected random graph with 1001 nodes, starting with 5 colours and working up to 50 max**
```
./colouring.exe -n 1001 -p 1 -c 5 -C 50
```
**colour a random graph with 300 nodes and 70% probability for each edge, using 50 agents that move twice on each turn, save the results and run it on 10 different graphs**
```
./colouring.exe -n 300 -p 0.7 -a 50 -m 2 -A 10 -S
```