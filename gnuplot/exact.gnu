set title "Execution Time of the exact algorithm"
set xlabel "number of vertices"
set ylabel "time in microseconds (10^-6 seconds)"

f(x) = a * 2 ** x

fit f(x) '/home/acki/CLionProjects/projectMBP-2/report/data/exact_25.dat' via a

set autoscale xy

label_f = sprintf("%.2f * 2^x", a)

plot '/home/acki/CLionProjects/projectMBP-2/report/data/exact_25.dat' with lines title '25%', f(x) title label_f, '/home/acki/CLionProjects/projectMBP-2/report/data/exact_50.dat' with lines title '50%', '/home/acki/CLionProjects/projectMBP-2/report/data/exact_75.dat' with lines title '75%