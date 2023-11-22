#!/usr/bin/bash

EXECUTABLE=./build/projectMBP


mkdir -p ./build/graph_gen

for PROB in .25 .5 .75 ; do
  for SIZE in 25 100 1000 3000 10000 ; do
    $EXECUTABLE generate -n $SIZE -p $PROB -f ./build/graph_gen/random_${SIZE}_${PROB}.in
  done
done