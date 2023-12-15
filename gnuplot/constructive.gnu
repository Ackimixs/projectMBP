set title "Execution Time of the constructive algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = a * x ** 2

fit f(x) '/home/acki/CLionProjects/projectMBP-2/report/data/constructive_25.dat' using 1:2 via a

plot '/home/acki/CLionProjects/projectMBP-2/report/data/constructive_25.dat' with lines title '25%', '/home/acki/CLionProjects/projectMBP-2/report/data/constructive_50.dat' with lines title '50%', '/home/acki/CLionProjects/projectMBP-2/report/data/constructive_75.dat' with lines title '75%', f(x) title 'f(n) = a * n ** 2'