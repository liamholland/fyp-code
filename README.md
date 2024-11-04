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

## Installation

- clone the repo
- compile `colouring.c` with gcc or whatever compiler you want to use
```
g++ ./colouring -o ./colouring.exe
```

## Usage

- Run the executable you compiled from the command line with some variation of the following options
```
usage: colouring.exe [options]
options:
-n [integer]      set the number of nodes in the graph
                    default is 10
-v                set verbose mode on
                    prints the graph when the colouring is complete
                    default is off
-g [generator]    set the generator
                    sets the graph generator function to use
                    there are currently two different types of graphs you can use
                    o: ring graph; undirected graph where each node has two neighbours (default)
                    r: random graph; a graph where each edge has a p% chance of existing
                      options:
                        -p [float]      probability (as a floating point number between 0 and 1)
                                          probability that each edge of the graph exists
                                          default is 0.5
                    b: bipartite graph; a graph of two disjoint subsets
                      options:
                        -s [integer]    set one; the number of nodes in the first subset
                                          the default is to split the number of nodes in two
-m [integer]      set the max iteration on random colour
                    default is 100
                    random colour is the only colouring algorithm at the moment
```

#### Example Usage
**colour a ring graph with 51 nodes and 10000 iterations per run of random colour**
```
./colouring.exe -v -m 10000 -n 51
```
**colour a random graph which has a probability of 30% that each edge exists**
```
./colouring.exe -v -g r -p 0.3
```
**colour a bipartite graph with 2 nodes in the first set and 4 in the second**
```
./colouring.exe -v -g b -n 6 -s 2
```
