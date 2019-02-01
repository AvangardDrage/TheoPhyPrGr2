set terminal pdf
set output "plot.pdf"
set size square

set title "Electric potential"
set xlabel "x"
set ylabel "y"
set rmargin at screen 0.8
set lmargin at screen 0.15

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
h = 0.05

plot [0:10] [0:10] "solution.dat" using 1:2:3 with image notitle


set title "Electric field"
plot [0:10] [0:10] "solution.dat" using 1:2:4 with image notitle



set title "Electric field"
plot [0:10] [0:10] "solution.dat" using 1:2:4 with image notitle, \
	"quiver.dat" \
	u ($1 - h*0.5*$5):($2 - h*0.5*$6):(h*$5):(h*$6)\
	with vectors head size 0.04,40,20 filled lc 'grey' notitle

