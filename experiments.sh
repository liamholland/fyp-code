NUMBER_OF_NODES=100
NUMBER_OF_AUTO_RUNS=2
MAXIMUM_ITERATIONS=5000


# UNLIMITED NUMBER OF COLOURS

# random kernel
for p in $(seq 0.1 0.1 1)
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S -M $MAXIMUM_ITERATIONS -k r
done

# decrementing kernel
for p in $(seq 0.1 0.1 1)
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S -M $MAXIMUM_ITERATIONS -k d
done

# incrementing kernel
for p in $(seq 0.1 0.1 1)
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S -M $MAXIMUM_ITERATIONS -k i
done


# INCREASING LIMITS

# random kernel
for k in 5 10 25 50 100 200 250
do
    for p in $(seq 0.1 0.1 1)
    do
        ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -c $k -S -M $MAXIMUM_ITERATIONS -k r
    done
done

# decrementing kernel
for k in 5 10 25 50 100 200 250
do
    for p in $(seq 0.1 0.1 1)
    do
        ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -c $k -S -M $MAXIMUM_ITERATIONS -k d
    done
done

# incrementing kernel
for k in 5 10 25 50 100 200 250
do
    for p in $(seq 0.1 0.1 1)
    do
        ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -c $k -S -M $MAXIMUM_ITERATIONS -k i
    done
done

#minimum kernel
for k in 5 10 25 50 100 200 250
do
    for p in $(seq 0.1 0.1 1)
    do
        ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -c $k -S -M $MAXIMUM_ITERATIONS -k m
    done
done