#!/usr/bin/bash

EXECUTABLE=./"$1"/projectMBP

mkdir -p ./"$1"/graph_gen

for PROB in 25 50 75
do
  for SIZE in 10 28 100 1000 3000 10000
  do
    $EXECUTABLE generate -n $SIZE -p .$PROB -o ./"$1"/graph_gen/random_${SIZE}_${PROB}.in --debug
  done
done

# head -n -1 ../src/model/Constants.hpp > temp && mv temp ../src/model/Constants.hpp
# echo "#define NO_LOG" >> ../src/model/Constants.hpp