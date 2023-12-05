#!/usr/bin/bash

EXECUTABLE=./"$1"/projectMBP

EXEC=./build/main

TYPE="constructive"

NUM_TRIALS=30

RESULTS_DIR="./report/data"

for PROB in 25 50 75
do

  cat /dev/null > "$RESULTS_DIR/${TYPE}_${PROB}.dat"

  for SIZE in 10 100 120 180 200 220 280 300 320 380 400 420 480 500 520 580 600 650 700 750 800 850 900 950 1000
  do
    # Run for each vertex count a 100 times to get a better average
    TIME_EXEC=0

    for ((i=1; i <= NUM_TRIALS; i++)) ; do

      $EXECUTABLE generate -n $SIZE -p .$PROB -o ./instances/$TYPE/random_${SIZE}_${PROB}.in

      # Run the algorithm
      ACTUAL_TIME=$($EXECUTABLE algo $TYPE -i ./instances/$TYPE/random_${SIZE}_${PROB}.in -o ./results/$TYPE/random_${SIZE}_${PROB}.out)
      TIME_EXEC=$(expr $TIME_EXEC + $ACTUAL_TIME)

    done

    TIME_EXEC=$(expr $TIME_EXEC / $NUM_TRIALS)

    echo "$SIZE $TIME_EXEC" >> "$RESULTS_DIR/${TYPE}_${PROB}.dat"
  done

  # Create average .dat file with errors
  # (https://tex.stackexchange.com/a/158777)
  # awk '/^[0-9]/{if($1!=x&&length(x)!=0){print x, y/n, sqrt((n*sy-y*y)/n/(n-1));x=$1;y=$2;sy=$2*$2;n=1} else{x=$1;y+=$2;sy+=$2*$2;n+=1;}} END{print x,y/n, sqrt((n*sy-y*y)/n/(n-1))}' "$RESULTS_DIR/${TYPE}_${PROB}.dat" > "$RESULTS_DIR/${TYPE}_${PROB}_avg.dat"

done

# head -n -1 ../src/model/Constants.hpp > temp && mv temp ../src/model/Constants.hpp
# echo "#define NO_LOG" >> ../src/model/Constants.hpp