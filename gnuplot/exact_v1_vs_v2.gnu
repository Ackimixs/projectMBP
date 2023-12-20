set title "Execution Time of the exact algorithm v1 vs v2"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

plot for [i in "0 25 50 75 100"] '../report/data/exact_V1_'.i.'.dat' using 1:2 with lines title "V1 ".i linecolor rgb "blue", for [i in "0 25 50 75 100"] '../report/data/exact_V2_'.i.'.dat' using 1:2 with lines title "V2 ".i linecolor rgb "red"