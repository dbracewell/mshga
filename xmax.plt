set term png;
set output 'r_xmax.png';
set size 1.5,1.5;
set origin 0.1,0.1;
set multiplot;
set size 0.75,0.75;
set origin 0.0,0.75;
set yrange [0:101];
set xtics 500;
set title 'SGA';
plot 'runs/r_xmax_sga_100runs.txt' using 1:2 with steps notitle;
set origin 0.75,0.75;
set title 'Random Immigrants GA';
plot 'runs/r_xmax_riga_100runs.txt' using 1:2 with steps notitle;
set origin 0.4,0.0;
set title 'MSHGA';
plot 'runs/r_xmax_mshga_100runs.txt' using 1:2 with steps notitle;
unset multiplot;
