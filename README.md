# Graph project g1

Killian, Romain, Paul K, Paul B

# How to use
## Compilation

go to the root of the project then make sure you have cmake version : \n
Then run : 
```c++
cmake -S . -b build
cmake build
cd build
./projectMBP [args...]
```

#### Generate graph
use `./projcetMPB generate [args...]` \n
options : -n, --nodes <int>  => number of node of the graph. \n
								-p, --probabilities <float> => probability to have an edge between two verticies, the number must be between 0 and 1 \n
								-o, --output <string> => path to output file that would be generated by the program \n
\n
use `./projectMBP generate --help` for more \n

### Run algorithm
use `./projectMBP algo <algoName> [args...]` \n
\n
algoName : the name of the algorithm you want to run inside that list : exact, constructive, local_search, tabu_search \n
 \n
without option the program will run every graph file inside the folder : `../instance/<algoName>/*` \n
The outp\nut will be inside the the folder `../result/<algoName>/<name of the original file but with .out extension>` \n
\n
If you want to run custom graph you have to set options : \n
			-i, --input <string> => path to the input file \n
			-o, --output <string> => path to the output file \n
\n
use `./projectMBP algo --help` for more \n

### Test algorithm
use `./projectMBP test <algoName> [args...]` \n
 \n
algoName : the name of the algorithm you want to run inside that list : exact, constructive, local_search, tabu_search \n
 \n
options :  \n
				-s, --size <list of int> => the size of the graph to test \n
				-p, --prob <list of int> => the probabilies to have an edge, should be between 0 and 100 \n
				--repeat <int> => number of time the program will test the graph for the same value to have a good average \n
 \n
The program will run the algorithm for every probabilities and for every size of graph \n
 \n
use `./projectMBP test --help` for more. \n
		
