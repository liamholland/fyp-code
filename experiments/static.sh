NUMBER_OF_NODES=1000
NUMBER_OF_AUTO_RUNS=10
MAXIMUM_ITERATIONS=50000


# UNLIMITED NUMBER OF COLOURS

# random kernel
for p in $(seq 0.1 0.1 1)
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S res/r_unl -M $MAXIMUM_ITERATIONS -k r
done

# decrementing kernel
for p in $(seq 0.1 0.1 1)
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S res/d_unl_ -M $MAXIMUM_ITERATIONS -k d
done

# incrementing kernel
for p in $(seq 0.3 0.1 1)
do
    ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -S res/i_unl_ -M $MAXIMUM_ITERATIONS -k i
done


# INCREASING LIMITS

# random kernel
for k in 2 50 500 800
do
    for p in $(seq 0.1 0.1 1)
    do
        ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -c $k -C $k -S res/r_lmtd_$k\_ -M 10000 -k r
    done
done

# decrementing kernel
for k in 2 50 500 800
do
    for p in $(seq 0.1 0.1 1)
    do
        ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -c 800 -C 800 -S res/d_lmtd_800_ -M 10000 -k d
    done
done

# incrementing kernel
for k in 2 50 500 800
do
    for p in $(seq 0.1 0.1 1)
    do
        ./colouring -n $NUMBER_OF_NODES -p $p -A $NUMBER_OF_AUTO_RUNS -c $k -C $k -S res/i_lmtd_$k\_ -M 10000 -k i
    done
done

# immutable nodes
for a in 950 850 750 650 500
do
    for p in 0.2 0.5 0.8
    do
        ./colouring -n $NUMBER_OF_NODES -p 0.5 -A 5 -S res/imm_$a\_ -M $MAXIMUM_ITERATIONS -k m -a $a -m 0
    done
done