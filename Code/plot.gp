set terminal pdf
set output "plot.pdf"

set title "Electric potential between two parallel plates"
set xlabel "x"
set ylabel "y"
set rmargin at screen 0.8
set lmargin at screen 0.15
set palette defined ( 0 "#000090",\
                      1 "#000fff",\
                      2 "#0090ff",\
                      3 "#0fffee",\
                      4 "#90ff70",\
                      5 "#ffee00",\
                      6 "#ff7000",\
                      7 "#ee0000",\
                      8 "#7f0000")
set cblabel "f(x,y)"
plot [0:10] [0:10] "plates.dat" using 1:2:3 with image notitle

set title "Electric field between two parallel plates"
plot [0:10] [0:10] "plates.dat" using 1:2:4 with image notitle

