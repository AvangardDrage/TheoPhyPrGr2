#!/bin/bash

rm time*.dat
clear
make time
./time.exe

gnuplot <<- EOF
  #set terminal pdf color
  set terminal postscript enhanced color font "Helvetica, 20"

  set key top left

	set xlabel "Grid size"
	set ylabel "Computational time"
	set logscale y
	#unset logscale

	set output "time.eps"
	set title "Computational time of the three methods for different grid sizes"
  set xrange [50:250]
	plot "time1.dat" using 1:2 pt 2 ps 1 lc rgb '#8f00b3' title "SOR", \
  "time2.dat" using 1:2 pt 2 ps 1 lc rgb '#4775d1' title "Gauss-Seidel", \
  "time3.dat" using 1:2 pt 2 ps 1 lc rgb '#ff8c1a' title "Jacobi"


EOF
