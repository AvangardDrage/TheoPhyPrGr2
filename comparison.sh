#!/bin/bash

rm *.dat
clear
make comparison
./comparison.exe


gnuplot <<- EOF
	set terminal pdf color
	set output "comparison.pdf"

	set key top left

	set title "Converge of the numerical methods for parallel plate capacitors in an N x N grid"
	set xlabel "N"
	set ylabel "Iterations"
	set logscale y

	plot "comparison.dat" using 1:2 pt 2 ps 0.6 lc rgb '#8f00b3' title "SOR", \
	     "comparison.dat" using 1:3 pt 2 ps 0.6 lc rgb '#4775d1' title "Gauss-Seidel", \
	     "comparison.dat" using 1:4 pt 2 ps 0.6 lc rgb '#ff8c1a' title "Jacobi"
EOF

xdg-open comparison.pdf
