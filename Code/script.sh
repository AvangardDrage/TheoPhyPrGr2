#!/bin/bash

clear

echo "Enter the number of rows:"
read rows

echo "Enter the number of columns:"
read cols

#need to change main.cpp such that it accepts command line arguments
./solver.exe ${rows} ${cols}

gnuplot <<- EOF
  set terminal pdfcairo dashed enhanced
  set output "plot.pdf"
  set size square


  set xlabel "x"
  set ylabel "y"
  set rmargin at screen 0.8
  set lmargin at screen 0.15
  unset clabel
  unset key

  #set palette defined ( 0 "#000090",\
                        1 "#000fff",\
                        2 "#0090ff",\
                        3 "#0fffee",\
                        4 "#90ff70",\
                        5 "#ffee00",\
                        6 "#ff7000",\
                        7 "#ee0000",\
                        8 "#7f0000")


  set palette defined ( 0 "#1212B0",\
                        1 "#242FE6",\
                        2 "#1398FF",\
                        3 "#0CFAEA",\
                        4 "#77F354",\
                        5 "#ffee00",\
                        6 "#ff7000",\
                        7 "#E11313",\
                        8 "#950101")
  #vector scale
  h = 0.1


  set title "Electric potential (numerical)"
  plot [0:${rows}-1] [0:${cols}-1] "test_solution.dat" using 1:2:3 with image

  set title "Electric potential (analytical)"
  plot [0:${rows}-1] [0:${cols}-1] "solution_new.dat" using 1:2:3 with image

  set title "Errors"
  plot [0:${rows}-1] [0:${cols}-1] "test_solution.dat" using 1:2:6 with image

  set title ""
  set dgrid3d 100,100,2
  set view 10,30,1.2,5

  #set pm3d lighting primary 0.3 specular 0.6
  #splot [-4.95:4.95] [-4.95:4.95] "solution.dat" using 1:2:6 with pm3d

  set title "Electric field"
  plot [0:${rows}-1] [0:${cols}-1] "test_solution.dat" using 1:2:4 with image

  set contour base
  unset surface
  set dgrid3d 10,10,4
  set cntrparam bspline
  set cntrparam levels incremental -8, 2, 8
  set table "cont.dat"
  splot "test_solution.dat" u 1:2:3
  unset table


  set title "Electric field"
  set linestyle 1 lt 2 lc rgb "#77000000"
  plot [0:${rows}-1] [0:${cols}-1] "test_solution.dat" using 1:2:4 with image, \
  	"quiver.dat" u ($1 - h*0.5*$5):($2 - h*0.5*$6):(h*$5):(h*$6)\
  	with vectors head size 0.04,40,20 filled lc 'black', \
  	"cont.dat" u 1:2:3 with lines ls 1

EOF

xdg-open plot.pdf
