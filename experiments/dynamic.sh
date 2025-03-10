NUMBER_OF_NODES=1000
NUMBER_OF_AUTO_RUNS=10
MAXIMUM_ITERATIONS=50000

# demonstrate robustness
for p in 0.2 0.5 0.8 
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S res/dyn_n_ -M $MAXIMUM_ITERATIONS -k m -d n
done

for p in 0.2 0.5 0.8 
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S res/dyn_e_ -M $MAXIMUM_ITERATIONS -k m -d e
done

# identify poor constraints with threshold
# run this a couple of times with different threshold values
for p in 0.2 0.5 0.8 
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S res/dyn_t_ -M $MAXIMUM_ITERATIONS -k m -d t
done


# reduce number of active agents in the graph
