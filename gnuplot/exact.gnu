set title "Execution Time of the exact algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = a * 2 ** x

fit f(x) '../report/data/exact_25.dat' using 1:2 via a

plot for [i in "0 25 50 75 100"] '../report/data/exact_'.i.'.dat' using 1:2 with lines title ''.i, f(x) title "a * 2 ** x" linecolor rgb "black"