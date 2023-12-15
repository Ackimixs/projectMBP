set title "Execution Time of the tabu search algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = a*x**2

fit f(x) '/home/acki/CLionProjects/projectMBP-2/report/data/tabu_search_25.dat' via a

plot '/home/acki/CLionProjects/projectMBP-2/report/data/tabu_search_25.dat' with lines title '25%', '/home/acki/CLionProjects/projectMBP-2/report/data/tabu_search_50.dat' with lines title '50%', '/home/acki/CLionProjects/projectMBP-2/report/data/tabu_search_75.dat' with lines title '75%', f(x) title 'f(x) = a*x^2'