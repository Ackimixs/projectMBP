set title "Execution Time of the local search algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = b * x**4 + (a * (x ** 2) * log(x))

fit f(x) '../report/data/local_search_25.dat' via a, b

plot for [i in "0 25 50 75 100"] '../report/data/local_search_'.i.'.dat' using 1:2 with lines title ''.i, f(x) title "b * x**3 + (a * (x ** 2) * log(x))" linecolor rgb "black"
