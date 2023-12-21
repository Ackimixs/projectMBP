set title "Execution Time of the exact algorithm vs the constructive heuristic"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

plot for [i in "0 25 50 75 100"] '../report/data/exact_V2_'.i.'.dat' using 1:2 with lines title "exact ".i linecolor rgb "blue",for [i in "0 25 50 75 100"] '../report/data/constructive_'.i.'.dat' using 1:2 with lines title "constructive ".i linecolor rgb "red",for [i in "0 25 50 75 100"] '../report/data/local_search_'.i.'.dat' using 1:2 with lines title "local_search ".i linecolor rgb "magenta", for [i in "0 25 50 75 100"] '../report/data/tabu_search_'.i.'.dat' using 1:2 with lines title "tabu_search ".i linecolor rgb "green"