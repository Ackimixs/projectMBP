set title "Execution Time of the constructive algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = (a * (x ** 2) * log(x)) + (b * x * log(x)) + (c * x)

fit f(x) '/home/acki/CLionProjects/projectMBP-2/report/data/constructive_50.dat' using 1:2 via a, b, c

plot for [i in "0 25 50 75 100"] '/home/acki/CLionProjects/projectMBP-2/report/data/constructive_'.i.'.dat' using 1:2 with lines title ''.i, f(x) title "a * x ** 2" linecolor rgb "black"