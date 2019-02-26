#!/bin/bash

#rm *.dat
rm grid*.eps
clear
make grid1
make grid2
./grid1.exe
./grid2.exe

gnuplot <<- EOF
  #set terminal pdf color
  set terminal postscript enhanced color font "Helvetica, 20"

	unset key

	set xlabel "Mesh size"
	set ylabel "Average error per grid point"
	#set logscale y
	unset logscale

	set output "grid1.eps"
	set title "Inaccuracy of SOR with increasing mesh size (Problem 1)"
	plot "grid_err1.dat" using 1:2 with lines lc rgb '#009933'

	unset logscale
	set output "grid2.eps"
	set title "Inaccuracy of SOR with increasing mesh size (Problem 2)"
	plot "grid_err2.dat" using 1:2 with lines lc rgb '#009933'

EOF

xdg-open grid1.eps
xdg-open grid2.eps
