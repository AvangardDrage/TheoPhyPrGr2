set terminal pdfcairo dashed enhanced 
set output "plot.pdf"
set size square


set xlabel "x"
set ylabel "y"
set rmargin at screen 0.8
set lmargin at screen 0.15
unset clabel
unset key


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
h = 50


set title "Electric potential (numerical)"
plot "n_SOR.dat" using 1:2:3 with image

set title "Electric field"
plot "n_SOR.dat" using 1:2:4 with image

set contour base
unset surface
set dgrid3d 10,10,4
set cntrparam bspline
set cntrparam levels incremental -4, 0.1, 4
set table "cont.dat"
splot "n_SOR.dat" u 1:2:3
unset table


set title "Electric field"
set linestyle 1 lt 2 lc rgb "#77000000"
plot "n_SOR.dat" using 1:2:4 with image, \
	"n_SOR_quiver.dat" u ($1 - h*0.5*$3):($2 - h*0.5*$4):(h*$3):(h*$4)\
	with vectors head size 0.04,40,20 filled lc 'black', \
	"cont.dat" u 1:2:3 with lines ls 1



set title "Electric potential (analytical)"
plot "a_sol_2.dat" using 1:2:3 with image

set title "Errors"
plot "a_sol_2_err.dat" using 1:2:3 with image


set title ""
set dgrid3d 100,100,2
set view 10,30,1.2,5

set pm3d lighting primary 0.3 specular 0.6
splot "a_sol_2_err.dat" using 1:2:3 with pm3d

