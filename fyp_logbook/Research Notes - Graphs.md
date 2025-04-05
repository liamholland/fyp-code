# Decentralised Graph Colouring
- [Complexity of decentralised graph colouring algorithm](https://www.hamilton.ie/ken_duffy/Downloads/cfl.pdf)
- Feder and Motwani algorithm
	- Randomised graph colouring algorithm
	- Exponential time and linear space
	- Centralised
- Leith and Clifford - Communication Free Learning (CFL) algorithm
	- Decentralised
	- Upper bounded time



# Basics of Graph Colouring
### Noteworthy Notes on Graph Theory from Second Year
- **Euler's formula for planar graphs**
	- For any (connected) planar graph with $v$ vertices, $e$ edges and $f$ faces, we have $$
v-e+f=2
$$
	- Also, every face has three edges and edges can be shared by two faces. So, $$
3f \leq 2e
$$
- What I might call a "coloured" graph is a graph that has been *properly* coloured
- A proper colouring is *minimal* if it takes the lowest number of colours possible
- This is called the *chromatic number* for a graph, and is denoted by $$
\chi(G)
$$
- For complete graphs $$
\chi(K_{n}) = n
$$
- For bipartite graphs $$
\chi(K_{p,q}) = 2
$$
- If a graph $G$ has $v$ vertices, then $$
1 \leq \chi(G) \leq v
$$
- Many different centralised algorithms exist to colour graphs, such as *Welsh-Powell Algorithm*

### Initial Research
#### Graph Colouring Book
##### Introduction to Graph Colouring
- You can see that a solution of n-1 colours is impossible if there are nodes with n connections in the graph
	- "the planar graph contains a set of four vertices that each have an edge between them... this tells us that different colours will be needed for each of these vertices"
- All planar graphs can be coloured with 4 colours
- A *simple* graph is a graph of undirected edges in which loops and multiple edges are forbidden
- Graph colouring problems can be defined generally as
	- Given a graph $G = (V, E)$, the *graph colouring problem* involves assigning each vertex $v \in V$ an integer $c(v) \in \{1, 2, \dots ,k\}$ such that
		- $c(u) \neq c(v) \forall \{u,v\} \in E$; and
		- $k$ is minimal.
- If a colouring has two adjacent nodes which are assigned the same colour, then it is *improper*
	- This situation is called a *clash*
- A colouring is *complete* if every node is assigned a colour
- A colouring is *feasible* if and only if it is both complete and proper
- A colouring is *optimal* if the number of colours is the same as the chromatic number of the graph
- An *independent set* is a subset of vertices $S \subseteq V$ that are *mutually nonadjacent*
	- I.e., $\forall u, v \in S, \{u,v\} \not\in E$
- A *clique* is the opposite
	- So, $\forall u, v \in S, \{u,v\} \in E$
- Graph colouring can also be viewed as a partitioning problem where a solution $S$ is represented by a set of $k$ colour classes
- [Graph Colouring Algorithms in C++](http://rhydlewis.eu/resources/gCol.zip)

##### Problem Complexity
- Algorithms that find $\chi(G)$ are called *exact* algorithms
- The Bell number (denoted $B_{n}$) of a set is the number of ways it can be partitioned into non-empty subsets
- A decision problem $\Pi$ is NP-complete if $\Pi \in NP$  and , for all other decision problems $\Pi ' \in NP, \Pi ' \propto \Pi$
	- Basically, a decision problem is NP-complete only when every other decision problem in NP can be reduced to it in polynomial time
	- In this case, the problem can be considered "at least as hard" as all other problems in NP
	- This sounds hard, but the following theorem shows that if we can reduce a problem to any known NP-complete problem, then it is also NP-complete
		- Let $\Pi_{1} \in NP$, $\Pi_{2} \in NP$, and let $\Pi_{1}$ be NP-complete. Then $\Pi_{2}$ is also NP-complete whenever $\Pi_{1} \propto \Pi_{2}$
		- **Proof:** Since $\Pi_{1}$ is NP-complete, by the above definition of decision problems, we have $\Pi ' \propto \Pi_{1} \forall \Pi ' \in NP$. Since $\Pi_{1} \propto \Pi_{2}$, it is also true that $\Pi ' \propto \Pi_{2} \forall \Pi ' \in NP$. Hence, $\Pi_{2}$ is NP-complete
	- This, of course means that we must have at least one problem that we know to be NP-complete without use of this theorem, which others can be reduced to in polynomial time
		- The problem used for this is the Boolean Satisfiability (SAT) problem
			- It has been shown that any decision problem in NP can be converted in polynomial time to a corresponding instance of SAT such that the instance of SAT will be satisfiable if and only if the original decision problem is answerable with "yes"
			- As such, if we could solve SAT in polynomial time, we could solve *any* decision problem in NP in polynomial time
- Gadget graphs, such as the OR-gadget graph, can be used to represent Boolean operations as graph colouring problems
	- ![[Pasted image 20241012135912.png]]

#### Paper on Decentralised Approaches to Graph Colouring
- No research on the effect of decentralised approaches on different graph topologies in the graph colouring domain?
- The performance of a graph colouring approach degrades as the number of *edges* increases
- [Seven Bridges of Königsberg problem](https://en.wikipedia.org/wiki/Seven_Bridges_of_K%C3%B6nigsberg)
- A graph is *regular* if all of its vertices have the same degree
- Erdos-Rényi model is the standard for producing random graphs
- Graphs can have theoretic bounds for the number of colours
	- If the graph $G$ has $n$ vertices and $e$ edges, then $$
e > \frac{n^{2}}{4}
\implies \chi(G) \geq 3
$$
	- This is true because $G$ must contain a triangle
	- The upper bound of $\chi(G)$ is at most the maximum degree plus one unless the graph is a complete graph or an odd cycle
- There are a number of nature inspired approaches to decentralised graph colouring
	- Ant Colonies 
		- Studied as a reference for decentralised graph colouring approaches
		- Other solutions are generally variations on this
	- Naked blind mole rat algorithm
		- Colony (cluster of local nodes) compete in scavenging for food (solutions)
		- Similar to searching the solution space
	- Intelligent water drop algorithm
		- Maintain a population of "water drops"
		- "Drops" move around the solution space by moving from one solution to another
- Graph Neural Networks are an approach using machine learning to solve GCP
	- Nodes and colours are assigned vector embeddings
	- Embeddings are initially random but are refined in training
	- Use two adjacency matrices; vertex-to-vertex and vertex-to-colour
- Solving the problem in parts is a multi-level approach
	- Coarsen the graph; reduce while maintaining "essential" feature
	- Make use of Tabu search in reverse order on each of the coarsened problems
	- "...does not push the envelope in terms of optimization..."
- There are many different variations on GCP, such as face colouring, edge colouring, defective colouring (not finding feasible solutions intentionally)



# Algorithms
#### Ant Local Search and its efficient adaptation to graph colouring
- Variation on ant algorithms that allows each ant to be more "aggressive"
- Instead of working with the other ants, you apply a greedy approach
- Classically, at each step, ant solutions aim to be built step-by-step
	- At each step, an ant adds an element to the current partial solution
	- This addition is based on the short-term "profit" for the ant, as well as information gained by other ants
		- For example, if an ant adds a colour which clashes, that information must be shared
- In Ant Local Search, the approach is slightly different
	- Instead of the above, each ant is treated itself as a local search
	- In other words, it can make an arbitrary number of changes to the local graph
- In this paper, they talk about a [[Research Notes - Graphs#Tabu Search|tabu]] approach where you find neighbour solutions by taking an uncoloured node and applying a colour to it, then remove the colour from each node adjacent to the node you coloured
	- It then becomes tabu to remove the colour from the graph
	- You measure the quality of the solution by the number of uncoloured nodes
- The way this is applied to an any algorithm is by having each ant increase the "trail" of a colour class if any two given nodes were given the same colour by an ant
	- This information is retained for ants in later generations, which should lead to that colour class being applied to more nodes
	- It was found that the optimal number of ants is between 5 and 10

#### Tabu Search
- Metaheuristic approach
	- These algorithms find an approximate solution very quickly
	- versus brute force, which finds an exact solution very slowly
- Local search methods have a tendency to become in sub-optimal regions
	- Allows us to avoid local maxima in the graph which might graph the improvements of the solution
	- Makes this algorithm good for *non-convex search spaces*
- Principles of Tabu search
	- If we have no moves that are better for the algorithm, then we are allowed to accept "worsening" moves
	- prohibitions are introduced to discourage the search from coming back to previously-visited solutions
		- This is called the tabu list
- There are also a couple of features of the algorithm
	- Tabu tenure
		- Adding a move to the tabu list of a certain value
		- On each iteration the tabu tenure is decremented by one
		- A move can be accepted if its tenure is 0
	- Aspiration criteria
		- Criteria for accepting tabu moves
		- Aspiration criteria allows a tabu move to the be selected based on certain constraints
		- For example, if you know that a tabu move will result in a better global solution and all of the allowed moves are worse than the actual one
- You might start the search with a random initialisation

#### Evolutionary Algorithms
- Check out [[Week 7 - Learning in IR#Evolutionary Computation|notes on evolutionary computation from lecture]]

#### An ant-based algorithm for graph colouring
- Saved as ants.pdf
- Simpler implementation of [[Research Notes - Graphs#Ant Local Search and its efficient adaptation to graph colouring|ant local search]]
- The idea is just that each ant colours the graph, not that they work with a tabu search algorithm
- As opposed to increasing the trail of a colour class in the range of $1 \dots k$, you just start with $k$ colours and colour with one of those, then reduce $k$ by one if there are no conflicts at then end
	- This is similar to my random search implementation
- Begins the algorithm by finding an estimate colouring using another algorithm, MXRLF
- They *perturb* the current colouring if there is no change in the available colours for some amount of time
	- They do this by recolouring the nodes adjacent to conflicting nodes with 80% of the available colours
- Similar to the other ant algorithm, the stopping condition is a certain number of cycles, or an amount of time, as opposed to some defined state of the graph



# Applications
#### Graph Colouring and Compilers
![](https://youtu.be/K3mi2m7ccDQ?si=LCv3rqmzPxHsGIPX)
- Any possibility of decentralised approaches making a difference here?



# Graph Types
#### Leighton Graphs?
- *TODO*

#### Flat Graphs?
- *TODO*


# Dynamic Graphs
- MIT lecture I ![](https://www.youtube.com/watch?v=XZLN6NxEQWo&t=146s)
- MIT lecture II![](https://www.youtube.com/watch?v=L7ywsci9ujo)
- 


# Visualisation
![](https://www.youtube.com/watch?v=2bVhyB7Av8s)


# Aims
- Investigate decentralised graph colouring
	- Algorithms
	- Applications
- Investigate decentralised approaches to managing dynamically changing graphs
	- In other words, can we use a decentralised approach to continually optimise the colouring of a graph
	- Imagine a wifi network where people are constantly walking in and out of the reach of the network with different devices
	- 
- Relate to computing



# Size of Array Hack
https://medium.com/@bmqube/find-size-of-an-array-using-pointer-hack-in-c-c-2c1c6743e12e



# Prior Research
https://link.springer.com/article/10.1007/s10589-016-9862-9#citeas
simple colouring algorithm

https://www.researchgate.net/publication/320071527_Fast_Responsive_Decentralized_Graph_Coloring
wireless networking algorithm


#fyp 