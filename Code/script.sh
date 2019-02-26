#!/bin/bash

rm *.dat
clear

echo "Enter the number of rows or columns for a square grid (in pixels):"
read N

./solver.exe ${N}


if [ -e a_sol.dat ]
then
	gnuplot <<- EOF
		set terminal pdfcairo dashed enhanced
		set output "plot.pdf"
		unset clabel
		unset key
		set size square


		set palette defined ( 0 "#1212B0",\
		                      1 "#242FE6",\
		                      2 "#1398FF",\
		                      3 "#0CFAEA",\
		                      4 "#77F354",\
		                      5 "#ffee00",\
		                      6 "#ff7000",\
		                      7 "#E11313",\
		                      8 "#950101")





		set title "Electric potential (numerical)"
		plot [0:${N}-1] [0:${N}-1] "n_SOR.dat" using 1:2:3 with image

		set title "Electric potential (analytical)"
		plot [0:${N}-1] [0:${N}-1] "a_sol.dat" using 1:2:3 with image

		set title "Errors"
		plot [0:${N}-1] [0:${N}-1] "a_sol_err.dat" using 1:2:3 with image

		set title ""
		set dgrid3d 100,100,4
		set view 10,30,0.8,7
		set ticslevel 0

		set pm3d lighting primary 0.1 specular 0.6
		splot [0:${N}-1] [0:${N}-1] "a_sol_err.dat" using 1:2:3 with pm3d


		set title "Electric field"
		plot [0:${N}-1] [0:${N}-1] "n_SOR.dat" using 1:2:4 with image


		#Extrapolate min and max values for potential and electric field
		stats "n_SOR.dat" using 3 name "POTENTIAL" nooutput
		stats "n_SOR.dat" using 4 name "ELECTRIC" nooutput

		h = 15/ELECTRIC_max


		set contour base
		unset surface
		set dgrid3d 100,100,4
		set cntrparam bspline
		set cntrparam levels incremental POTENTIAL_min, (POTENTIAL_max-POTENTIAL_min)/10, POTENTIAL_max
		set table "cont.dat"
		splot "n_SOR.dat" u 1:2:3
		unset table

		set title "Electric field"
		set linestyle 1 lt 2 lc rgb "#77000000"
		plot [0:${N}-1] [0:${N}-1] "n_SOR.dat" using 1:2:4 with image, \
			"n_SOR_quiver.dat" u (column(1) - h*0.5*column(3)):(column(2) - h*0.5*column(4)):(h*column(3)):(h*column(4))\
			with vectors head size 0.04,40,20 filled lc 'black', \
			"cont.dat" u 1:2:3 with lines ls 1
	EOF

xdg-open plot.pdf


else
	gnuplot <<- EOF
		set terminal pdfcairo dashed enhanced
		set output "plot.pdf"
		unset clabel
		unset key
		set size square


		set palette defined ( 0 "#1212B0",\
		                      1 "#242FE6",\
		                      2 "#1398FF",\
		                      3 "#0CFAEA",\
		                      4 "#77F354",\
		                      5 "#ffee00",\
		                      6 "#ff7000",\
		                      7 "#E11313",\
		                      8 "#950101")





		set title "Electric potential (numerical)"
		plot [0:${N}-1] [0:${N}-1] "n_SOR.dat" using 1:2:3 with image


		set title "Electric field"
		plot [0:${N}-1] [0:${N}-1] "n_SOR.dat" using 1:2:4 with image


		#Extrapolate min and max values for potential and electric field
		stats "n_SOR.dat" using 3 name "POTENTIAL" nooutput
		stats "n_SOR.dat" using 4 name "ELECTRIC" nooutput

		h = 15/ELECTRIC_max


		set contour base
		unset surface
		set dgrid3d 100,100,4
		set cntrparam bspline
		set cntrparam levels incremental POTENTIAL_min, (POTENTIAL_max-POTENTIAL_min)/10, POTENTIAL_max
		set table "cont.dat"
		splot "n_SOR.dat" u 1:2:3
		unset table

		set title "Electric field"
		set linestyle 1 lt 2 lc rgb "#77000000"
		plot [0:${N}-1] [0:${N}-1] "n_SOR.dat" using 1:2:4 with image, \
			"n_SOR_quiver.dat" u (column(1) - h*0.5*column(3)):(column(2) - h*0.5*column(4)):(h*column(3)):(h*column(4))\
			with vectors head size 0.04,40,20 filled lw 0.7 lc 'black', \
			"cont.dat" u 1:2:3 with lines ls 1
	EOF

	xdg-open plot.pdf

fi
