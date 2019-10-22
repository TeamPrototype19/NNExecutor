mkdir -p to_iv3
 gdb --args ./nne -p nn_iv3.cgo -i tv_iv3/tv_conv1_3x3_s2_i.dat -o out_iv3.dat
#           ./nne -p nn_iv3.cgo -i tv_iv3/tv_conv1_3x3_s2_i.dat -o out_iv3.dat

mv conv*.dat data*.dat ip*.dat pool*.dat relu*.dat prob*.dat to_iv3 
