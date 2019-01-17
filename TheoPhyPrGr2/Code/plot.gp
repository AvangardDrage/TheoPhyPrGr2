set terminal jpeg
set output "plot.jpg"

set title "Electric potential between two parallel plates"
set xlabel "x"
set ylabel "y"
set rmargin at screen 0.8
set lmargin at screen 0.15
set palette rgbformulae 7,5,15
set cblabel "f(x,y)"
plot [0:10] [-1:0.5] "plates.dat" using 1:2:3 with image notitle

