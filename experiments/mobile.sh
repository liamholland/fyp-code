NUMBER_OF_NODES=1000
NUMBER_OF_AUTO_RUNS=5
MAXIMUM_ITERATIONS=50000

for m in 1 2 5
do
    for a in 10 100 500
    do
        for p in 0.2 0.5 0.8
        do
            ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S res/mob_$a\_ -M $MAXIMUM_ITERATIONS -k m -w o -a $a -m $m
        done
    done
done
