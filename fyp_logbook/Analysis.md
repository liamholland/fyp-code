# Minimum Local Search
##### Experiment
`./colouring -n 1000 -p $p -k m -A 10 -S -c 1` for $p \in \{0.1, 0.2, \dots, 1\}$
Compares the ability of the minimum local search to colour the graph with increasing limits on the number of colours for varying densities of graphs


##### Results
**Conflicts Over Number of Iterations**
![[Pasted image 20250206202015.png]]


**Time to Colour Graph Over Density**
![[Pasted image 20250206202343.png]]


**Number of Colours Over Density**
![[Pasted image 20250206202620.png]]


**Number of Iterations Over Density**
![[Pasted image 20250206202813.png]]


# Random Resolver
- Resolves picks a random colour to resolve conflicts if the node is in conflict

### Results

##### Unlimited

**Conflicts over iterations**
![[Pasted image 20250210115857.png]]

**Conflicts over Iterations without p=1**
![[Pasted image 20250210121144.png]]

**Time to Colour Graph Over Density**
![[Pasted image 20250217153603.png]]

**Number of Colours Over Density**
![[Pasted image 20250217153752.png]]

**Number of Iterations Over Density**
![[Pasted image 20250217153824.png]]


##### Limited
- Fails at every density with 2 colours
- Fails at every density with 50 colours
- Fails with 500 colours after 0.5 density
	- Weirdly reports that it used exactly 500 colours each time at 0.5
	- This suggests it struggled at first but was able to narrow it down
	- It takes noticeably more iterations at 0.5 than before
	- You can kind of see this by plotting colours and conflicts over density ![[Pasted image 20250217155104.png]]
- Similar thing with 800 colours above 0.7
	- The point at which is cannot be solved is 0.9
	- It uses max colours at 0.8
	- Colours vs conflicts for this data set looks like this: ![[Pasted image 20250217155942.png]]



# Colour Blind (Incrementing)

### Results
##### Unlimited

**Conflicts over iterations**
![[Pasted image 20250217164717.png]]
- this is limited to iteration 1100


**Time to Colour Graph Over Density**
![[Pasted image 20250217165450.png]]

**Number of Colours Over Density**
![[Pasted image 20250217165540.png]]

**Number of Iterations Over Density**
![[Pasted image 20250217165628.png]]
- Note here that the early high number of iterations is due to a couple of nodes not being able to be solved


##### Limited
- Comes close to succeeding with around 0.4/0.5 density and 500 colours
- Similar with 800 colours, but is close around 0.4 - 0.8 density


**2 colours, 0.1**
![[Pasted image 20250218180322.png]]

**2 colours, 0.5**
![[Pasted image 20250218180357.png]]

**2 colours, 1**
![[Pasted image 20250218180435.png]]


**50 colours, 0.1**
![[Pasted image 20250218180512.png]]

**50 colours, 0.5**
![[Pasted image 20250218180629.png]]

**50 colours, 1**
![[Pasted image 20250218180711.png]]

**500 colours, 0.1**
![[Pasted image 20250218180752.png]]

**500 colours, 0.5**
![[Pasted image 20250218180826.png]]

**500 colours, 1**
![[Pasted image 20250218180858.png]]


**800 colours, 0.1**
![[Pasted image 20250218180951.png]]

**800 colours, 0.5**
![[Pasted image 20250218181022.png]]

**800 colours, 1**
![[Pasted image 20250218181050.png]]




# Colour Blind (Decrementing)

### Results
##### Unlimited

**Conflicts over iterations**
![[Pasted image 20250217170118.png]]

![[Pasted image 20250217170410.png]]
- this is limited to iteration 1100

![[Pasted image 20250217170704.png]]
- this is without p=1

![[Pasted image 20250217170748.png]]
- this is without p=1 and limited to iteration 1100


**Time to Colour Graph Over Density**
![[Pasted image 20250217171029.png]]

**Number of Colours Over Density**
![[Pasted image 20250217171104.png]]

**Number of Iterations Over Density**
![[Pasted image 20250217171137.png]]


##### Limited
- Begins to succeed with 500 colours at low densities (0.1, 0.2)
	- Is able to *almost* succeed up to 0.5
	- Similar story with 800 colours, but this time it can *almost* succeed up to 0.8

**2 colours, 0.1**
![[Pasted image 20250218172932.png]]

**2 colours, 0.5**
![[Pasted image 20250218173013.png]]

**2 colours, 1**
![[Pasted image 20250218173050.png]]

**50 colours, 0.1**
![[Pasted image 20250218173137.png]]

**50 colours, 0.5**
![[Pasted image 20250218173227.png]]

**50 colours, 1**
![[Pasted image 20250218173303.png]]

**500 colours, 0.1**
![[Pasted image 20250218173434.png]]

**500 colours, 0.5**
![[Pasted image 20250218173514.png]]

**500 colours, 1**
![[Pasted image 20250218173629.png]]

**800 colours, 0.1**
![[Pasted image 20250218174026.png]]

**800 colours, 0.5**
![[Pasted image 20250218174104.png]]

**800 colours, 1**
![[Pasted image 20250218174152.png]]






#fyp 
