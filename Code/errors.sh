#!/bin/bash

rm *.dat
clear

make error1
make error2

echo "Enter the number of rows:"
read rows

echo "Enter the number of columns:"
read cols

echo ""
echo "FIRST PROBLEM"
./error1.exe ${rows} ${cols}

echo ""
echo "SECOND PROBLEM"
./error2.exe ${rows} ${cols}

gnuplot <<- EOF
  set terminal postscript enhanced color font "Helvetica, 20"

  unset key
  set font "Helvetica, 25"
  set title "Inaccuracy of SOR with increasing number of iterations (Problem 1)"
  set xlabel "Iterations"
  set ylabel "Average error per grid point"
  set logscale y

  set output "errors1.eps"
  plot "err_compar1.dat" pt 2 ps 0.6 lc rgb '#33bbff' notitle

  set title "Inaccuracy of SOR with increasing number of iterations (Problem 2)"
  set xlabel "Iterations"
  set ylabel "Average error per grid point"
  set logscale y

  set output "errors2.eps"
  plot "err_compar2.dat" pt 2 ps 0.6 lc rgb '#33bbff' notitle


EOF

xdg-open errors1.eps
xdg-open errors2.eps
