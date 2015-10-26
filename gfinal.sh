out='gf.png'
gnuplot << PLOTTHIS
set term postscript eps enhanced color  "Helvetica" 32

set terminal png
set output "${out}"
set autoscale
unset log                              
unset label
set grid 
set title "Matrix Multiplication"
set key right top

set logscale x
set xrange [:3500]
#set yrange [:100]
set xtics (1,5,10,20,50,100,200,500,1000,2000,3000)
#set xtics (0.2,0.25,0.5,0.75,1)

set xlabel "Dimesion(n)"
set ylabel "Time(ms)"

##############################################################

plot "matmult.txt" title 'Using Threads' with linespoints ls 1,"matmuld.txt" title 'Direct Multiplication' with linespoints ls 1 lc rgb 'black'

##############################################################

##############################################################
pause mouse
PLOTTHIS


