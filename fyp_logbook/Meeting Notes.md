# 4/11/24
- Random graph implementation
	- Intuitive sense of how this can be applied to other algorithms
- Goal of the research project
	- Running code vs finding mathematical definitions? What is the balance
- Ant Local Search implementation
	- Applying weighting and trail to a new node
	- Increase the amount of local knowledge
- Different types of graphs
	- The test set graphs that all of the papers seem to use
	- Not that useful for dynamic changes
	- Lattice graph
- Dynamic graphs
	- Create a lot of graphs with varying probability to avoid having one with strange topology
	- Deleting an edge
	- Which edge is the best to remove
- Don't overthink it



# 12/11/24
- Incrementing the amount of knowledge a node has about a graph
	- I have been doing this with agents that move around, another option is to place an agent at every vertex and keep them stationary
	- Counting the number of conflicts to measure
- Simple approach
	- If there is a conflict, increase or decrease the colour of the node
	- The two different graphs you get based on the pattern of change
- Minimum approach
	- Two major changes here means that the graph no longer has conflicts
	- The agent finds the colours used in its locality, then applies the minimum colour possible to the node
	- It then moves based on two conditions
		- Move to the first uncoloured node, or if there is none
		- Move to the neighbour with the "biggest" colour
	- Added a crude centralised approach to measure the performance of this algorithm
- Next approaches
	- Move closer to probabilistic approaches
	- "Tabu list" for visited nodes on an agent
- Hyperparameter Tuning
- How to tell where the optimal position to modify the graph is using a decentralised approach?
- Need to make the tool capable of setting the maximum colour that the agents can use, then graph the conflicts based on that


# 17/1/25
- Best way to make the graphs dynamic
	- After running or during running?


# 29/1/25
- TSP - can you revisit nodes
- What is the format of the presentation
- The different generation models? What are they
	- Barabassi-Strogat - different distribution
	- Watts - connected section
- Maxamally something something something
- DONE:
	- Comparison between conflicts and degree
	- Bad actor
- TODO:
	- Timer
	- Some structural stuff maybe
	- More experiments
- Experiments
	- Increase density of the graph


# 24/2/25
- The performance of minimum local colour
	- When will it fail to colour the graph optimally?
- What I have:
	- Results of colouring experiments
- Next Up:
	- Bad actor demonstration
	- Threshold experiments
	- Dynamic destruction and addition demostrations


# 28/2/25
- Prior Research - what should this look like?



# 24/3/25
- Introduction - project objectives
	- Determine what the project objectives are
	- Focus on the implementation and design of algorithms
- What more needs to be included in the related work section, review the research so far
	- Specifically applications since there was a question over that
	- Sub optimal solutions
		- You can colour with k+1 colours faster but that means less optimal colouring
		- This is a *relaxation*
		- As well as the balance of colours vs conflicts
			- Airlines overbooking
		- Add this as a subsection to 2.2
		- Minimising colours vs no. conflicts
- Implementation
	- Use a toy graph to show how the algorithm actually works
	- Specific notes on the pseudocode
	- Explanation of some of the choices in relation to those
	- Assigning the colour to the agent
- Experimental results
	- Explanation of wave pattern and flat-top graphs
		- Need to put it in a formal way
	- Need to put in a summary
	- Dynamic experiments - anything else that needs to be shown?
		- Make nodes immutable in a centralised manner
		- Nodes are made immutable at the start of the process
		- How much immutability can we withstand?
		- We are benefitted by the amount of time we have before nodes become immutable
- Reflections
	- Add personal motivations to this section
	- Why choose C



#fyp 