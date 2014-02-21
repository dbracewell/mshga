set term png;
set output 'r_kp.png';
set size 1.5,1.5;
set origin 0.1,0.1;
set multiplot;
set size 0.75,0.75;
set origin 0.0,0.75;
set yrange [0:101];
set xrange [0:800]
set ylabel "Percentage Optimal"
set xtics 50;
set title 'SGA';
plot 'kp_sga' using 1:2 with steps notitle;
set origin 0.75,0.75;
set title 'Random Immigrants GA';
plot 'kp_riga' using 1:2 with steps notitle;
set origin 0.4,0.0;
set title 'MSHGA';
plot 'kp_mshga' using 1:2 with steps notitle;
unset multiplot;
