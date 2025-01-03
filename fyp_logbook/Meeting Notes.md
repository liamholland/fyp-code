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






#fyp 