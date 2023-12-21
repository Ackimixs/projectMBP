set title "Execution Time of the tabu search algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = a * (x + x ** 5)

fit f(x) '../report/data/tabu_search_25.dat' via a

plot for [i in "0 25 50 75 100"] '../report/data/tabu_search_'.i.'.dat' using 1:2 with lines title ''.i, f(x) title "a * (x + x ** 5)" linecolor rgb "black"