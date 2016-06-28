reset
set xrange[0:22050]
set zeroaxis
set grid

set xlabel "Frequency (Hz)"

set multiplot layout 3,1

plot "lpf-hamming.dat" u 2:4 t "Hamming" w l, \
     "lpf-blackman.dat" u 2:4 t "Blackman" w l

plot "lpf-hamming.dat" u 2:4 t "Low Pass Hamming" w l, \
     "hpf-hamming.dat" u 2:4 t "High Pass Hamming" w l

plot "bpf-hamming.dat" u 2:4 t "Band Pass Hamming" w l, \
     "bsf-hamming.dat" u 2:4 t "Band Stop Hamming" w l


unset multiplot
