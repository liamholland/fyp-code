for p in $(seq 0.1 0.1 1)
do
    ./colouring -n 1000 -p $p -A 5 -S -M 10000
done