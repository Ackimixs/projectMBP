set title "Execution Time of the tabu search algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = a * 100 * (x + x ** 3)

fit f(x) '/home/acki/CLionProjects/projectMBP-2/report/data/tabu_search_25.dat' via a

plot for [i in "0 25 50 75 100"] '/home/acki/CLionProjects/projectMBP-2/report/data/tabu_search_'.i.'.dat' using 1:2 with lines title ''.i, f(x) title "a * x ** 3" linecolor rgb "black"