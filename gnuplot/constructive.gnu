set title "Execution Time of the constructive algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = (a * (x + m * log(m))) + (d * x ** 2)

fit f(x) '../report/data/constructive_50.dat' using 1:2 via a, d, m

plot for [i in "0 25 50 75 100"] '../report/data/constructive_'.i.'.dat' using 1:2 with lines title ''.i, f(x) title "(a * (x + m * log(m))) + (d * x ** 2)" linecolor rgb "black"