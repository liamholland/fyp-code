NUMBER_OF_NODES=1000
NUMBER_OF_AUTO_RUNS=10
MAXIMUM_ITERATIONS=50000

# run minimum local search on different densities
for p in $(seq 0.1 0.1 1)
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S res/m_bm_ -M $MAXIMUM_ITERATIONS -k m
done