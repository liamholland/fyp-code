# Random Search
- Implementing random search was fairly easy, but the stopping condition on an algorithm which finds the chromatic number is not
- I have implemented an approach which begins with the number of nodes as the chromatic number, then whittles it down until it finds a solution with conflicts, at which point it knows that the previous solution was the correct colouring
- There are a couple of problems with this
	- The algorithm includes a `maxIterations` variable to prevent the algorithm from running forever, once this number is hit, the algorithm accepts whatever solution the process came up with. If the solution is incomplete, then it does not ask again
		- Increasing this number on larger graphs allows you to find lower numbers for the chromatic colour, as your odds increase that the colour chosen by a conflicting node will not cause conflicts
	- I am not finding the best solution with this approach, I am finding the first failed attempt at colouring the graph with random colours
	- The way the code is formatted, I am not really printing out the chromatic colour, but the maximum possible colour
		- Just because that is the maximum colour does not mean that every other colour is actually used in the graph, even if it is likely
		- I implemented a function to test this and actually it might be the same or 1 less than the max colour most of the time
		- Yep it is the same. Still useful to have the chromatic colour function though
	- Given a ring graph, with an odd number of nodes, you would expect to have $\chi(G) = 3$
		- This is the case when you run the code, but where you might expect only one node to be coloured with the third colour, it shows up all over the place
		- It still returns the chromatic colour, so using each colour the minimum number of times, is another constraint
		- I also wonder if working from 1..N instead of N..1 would make a difference in these results
- Example Output:
	- ![[Pasted image 20241029170701.png|400]]
	- Notice how many more iterations it takes to find a complete colouring towards the end
- Effect of iterations on results for a 100 node random graph with 50% probability
	- ![[Pasted image 20241029184419.png]]
- Next steps
	- Find a better algorithm to run on each node, which can better guess a colour which is unlikely to conflict with other nodes
		- ~~Start by doing something simple like starting with the node with the highest degree and colouring that one first~~
			- This is a centralised approach
		- Increment the colour instead of decrement it
	- Maybe try and find a better way to represent possible solutions; maybe an array which stores the colours and the chromatic colour as a `solution` struct?


# Simple Agent Algorithm - No Global Knowledge
- This algorithm is based on the idea of ant algorithms but has absolutely no global knowledge 
- There is also no information shared between generations of agents; they take the same action every time
- The agents are placed randomly, then move around the graph, changing the colour of the node if it is conflicting with its neighbours
- As expected, the number of conflicts drops off very fast, leading to a long period of time where we have no changes
- A random graph with 0.4 probability, 30 agents and 500 nodes produces the following results
	- ![[Pasted image 20241106164336.png]]
![[Pasted image 20241106164321.png]]
- Nearly completely solved after 46 iterations
- The question this immediately raises is what if we could reduce the remaining conflicts faster
	- Dynamic graph which drops the highest conflict edge each iteration/after a number of tries
	- Add a trail for the agents to find their way to conflicting nodes more effectively
- The function which changes the colour is also not satisfactory
	- I need some better way to select the colour that I want to use
	- Considering what colours the node's neighbours have would be a good place to start for that
- The sharp drop-off is also due to the fact that I count uncoloured nodes as conflicting
	- If I do not count uncoloured nodes as conflicting with each other, I get this ![[Pasted image 20241106170349.png]]
	- The alternative approach is to actually do a pass where we assign a random colouring or a colouring of 1 or the colouring of the degree of the node first, then use the colouring algorithm
- Applying a random colouring not only reduces the number of conflicts, but *dramatically* reduces the running time of the algorithm
	- Drastically fewer iterations are required ![[Pasted image 20241106171032.png]]
	- the agents have a lot less work to do
	- It also returns a far higher number of colours, since there is not as much restrictions on colours for each node
- Initialising each node with the colour $k = deg(n)$ gives similar results to not colouring the graph until the agents start to work on it
	- Single Run ![[Pasted image 20241106172526.png]]
	- Average of 10 runs ![[Pasted image 20241106183549.png]]
- the results up to now have been with a function that simply reduced the colour starting from the degree, resetting it if it got to 0
```C
//each "fish" makes changes to the graph
for(int f = 0; f < numFish; f++) {
	if(!fish[f]->colour){
		fish[f]->colour = fish[f]->degree;
	}

	//check for conflicts in neighbours
	for(int nb = 0; nb < fish[f]->degree; nb++) {
		if(fish[f]->neighbours[nb]->colour == fish[f]->colour) {
			fish[f]->colour--;

			if(!fish[f]->colour) {
				fish[f]->colour = fish[f]->degree + 1;
			}

			numChanges++;
			break;
		}

	}

	//the fish wanders in its locality
	for(int m = 0; m < numMoves; m++) {
		fish[f] = fish[f]->neighbours[rand() % fish[f]->degree];
	}

	conflictsAtIterationI[i] = findNumConflicts(colouringGraph, numNodes);
}
```
- I changed this so it was instead in the range $1 \dots deg(n)$ based on a modulo operation
```C
//each "fish" makes changes to the graph
for(int f = 0; f < numFish; f++) {

	//check for conflicts in neighbours
	for(int nb = 0; nb < fish[f]->degree; nb++) {
		if(fish[f]->neighbours[nb]->colour == fish[f]->colour) {
			fish[f]->colour = (fish[f]->colour + 1) % (fish[f]->degree + 1);

			if(!fish[f]->colour) {
				fish[f]->colour++;
			}

			numChanges++;
			break;
		}

	}

	//the fish wanders in its locality
	for(int m = 0; m < numMoves; m++) {
		fish[f] = fish[f]->neighbours[rand() % fish[f]->degree];
	}

	conflictsAtIterationI[i] = findNumConflicts(colouringGraph, numNodes);
}
```
- The results of a run the same as the previous, again averaged over 10 runs, produced the following results ![[Pasted image 20241107172323.png]]
	- This must be due to the fact that a lot of nodes end up at 1 at the start, if they are conflicting with any nodes around them, then this reduces as the agents begin to fix the conflicts
	- Another example, the same parameters but this time with 0.1 probability ![[Pasted image 20241107172943.png]]
	- And another, this time with 0.8 probability ![[Pasted image 20241107174726.png]]
	- Removing the initial colouring produces the same results but far slower (0.4 probability) (actually also 20 agents but its still slower with 30) ![[Pasted image 20241109120913.png]]


# Smarter Decentralised Approach
- Fluke run but kinda shows the goal ![[Pasted image 20241109125354.png]]
- The idea this time is to have the agents move and pick their colour more "intelligently"
- Example results from completed(?) algorithm: ![[Pasted image 20241109132256.png]]
- It actually applies colours too precisely, there are no conflicts to measure
- Next steps
	- Measure something to determine the performance of the algorithm
	- Determine how the agents are moving
		- Try to prevent them from moving to the same node
	- Determine if any parameters improve/reduce the performance of the algorithm as well as if the centralised algorithm is actually finding an optimal solution
- Is there a memory leak? weird how consecutive runs produce worse results ![[Pasted image 20241110222316.png]] ![[Pasted image 20241111114542.png]]
- ![[Pasted image 20241111114057.png]]
- When refactoring the code I realised I made a mistake in the agent colour which explains why the results are coming out like this
	- The problem was that I wrote the condition before I realised there will never be any conflicts in the graph
	- This means that I was condition making a change to a node on it conflicting with its neighbours or not having a colour assigned to it
	- This is why sometimes the results are better than others; it is completely predicated on the topology of the graph and where the agents are placed at the start
	- Changing this to always *try* and make a change to the graph means you get much better results, but it also means that once you get to 1000 nodes its basically guaranteed to hit the iteration limit (50000 in my tests)
	- The other problem is that it is far more likely to miss nodes, but I am not sure why that is the case yet since the movement is not predicated on changes being made to the graph
	- *Now* changes to the number of agents will actually have visible results on performance
	- ![[Pasted image 20241111172007.png]]
- I am running into a really strange issue where freeing the memory used in an integer array is causing the program to finish too early
	- not freeing `coloursInLocality` vs freeing it ![[Pasted image 20241111173058.png]]
	- I think it must be causing the compiler to produce strange code so im going to leave it out for the moment
	- I found the issue: the memory was allocated, but not initialised
		- Changing the `findWhichColoursInGraph` function to use `calloc` instead of `malloc` fixed the issue
		- The code still worked as expected because `!coloursInLocality[c]` will still resolve to false if the memory is not initialised
		- Only the free caused issues when you try to free memory that has nothing in it


# Generalised Decentralised Approach with Colour Limit
-  This approach uses the same algorithm as the previous, but now we are limiting the number of colours used in the graph
- Also, there is a stationary agent on each node, for the entire duration
- Running the minimum agent kernel on every vertex means that the algorithm runs pretty quickly
- For this experiment, I used a random graph with 0.4 probability, and averaged the data over 10 runs, there was a cap of 50000 iteration, but it got nowhere near that
- I began with a maximum of 5 colours, then used 50, 100, 250, and finally, 500
- The results made sense, but I need to find a way to increase the colour during the loop
- I implemented a minimum colour parameter and tested it with this command ![[Pasted image 20241115173104.png]]
- Simply incrementing the number of available colours each time we can no longer make any changes, the graph looks like this:  ![[Pasted image 20241115173023.png]]
- Printed Output: ![[Pasted image 20241115173748.png]]
- It is worth noting that this is basically the number of "uncolourable" nodes, since the minimum colour agent will not colour a node if there are no available colours
- Might be worth implementing an initialisation function
- I ran a similar experiment with moving agents as well (note I increased the break point to 50 for this) ![[Pasted image 20241115191516.png]]
- Here are the graphed results: ![[Pasted image 20241115191450.png]]
- Time to implement a timer :)
- One final note, I changed the kernel to the colourblindfish algorithm and I got a similar graph to before (still produces less than stellar colourings though) ![[Pasted image 20241115192051.png]]
- Lower bounded colour vs no lower bounded colour with agents on minimum colour ![[Pasted image 20241115192410.png]]
- I just feel like there is something I am missing in my implementation; some mistake or problem that I introduced when making the change to introduce a maximum colour parameter or refactoring and cleaning up the code
	- It is very possible that removing the percolations had this effect, so I might reintroduce that tomorrow and see if that helps when I do not have a lower bound on the colours set
- Setting a lower bound reduces the codes ability to improve on the benchmark? ![[Pasted image 20241117175936.png]]





#fyp 