echo "###### Inception V3 vector matching ######"

./fchksnr -t to_iv3/conv1_3x3_s2_i.dat             -r tv_iv3/tv_conv1_3x3_s2_i.dat                   -R to_iv3/report_conv1_3x3_s2_i.txt          -n conv1_3x3_s2_i
./fchksnr -t to_iv3/conv1_3x3_s2_o.dat             -r tv_iv3/tv_conv1_3x3_relu_o.dat                 -R to_iv3/report_conv1_3x3_s2.txt            -n conv1_3x3_s2
./fchksnr -t to_iv3/conv2_3x3_s1_o.dat             -r tv_iv3/tv_conv2_3x3_relu_o.dat                 -R to_iv3/report_conv2_3x3_s1.txt            -n conv2_3x3_s1
./fchksnr -t to_iv3/conv3_3x3_s1_o.dat             -r tv_iv3/tv_conv3_3x3_relu_o.dat                 -R to_iv3/report_conv3_3x3_s1.txt            -n conv3_3x3_s1
./fchksnr -t to_iv3/pool1_3x3_s2_o.dat             -r tv_iv3/tv_pool1_3x3_s2_o.dat                   -R to_iv3/report_pool1_3x3_s2.txt            -n pool1_3x3_s2
./fchksnr -t to_iv3/conv4_3x3_reduce_o.dat         -r tv_iv3/tv_conv4_relu_3x3_reduce_o.dat          -R to_iv3/report_conv4_3x3_reduce.txt        -n conv4_3x3_reduce
./fchksnr -t to_iv3/conv4_3x3_o.dat                -r tv_iv3/tv_conv4_relu_3x3_o.dat                 -R to_iv3/report_conv4_3x3.txt               -n conv4_3x3
./fchksnr -t to_iv3/pool2_3x3_s2_o.dat             -r tv_iv3/tv_pool2_3x3_s2_o.dat                   -R to_iv3/report_pool2_3x3_s2.txt            -n pool2_3x3_s2

./fchksnr -t to_iv3/inception_a1_1x1_o.dat         -r tv_iv3/tv_inception_a1_1x1_relu_o.dat          -R to_iv3/report_inception_a1_1x1.txt        -n inception_a1_1x1
./fchksnr -t to_iv3/inception_a1_5x5_reduce_o.dat  -r tv_iv3/tv_inception_a1_5x5_reduce_relu_o.dat   -R to_iv3/report_inception_a1_5x5_reduce.txt -n inception_a1_5x5_reduce
./fchksnr -t to_iv3/inception_a1_5x5_o.dat         -r tv_iv3/tv_inception_a1_5x5_relu_o.dat          -R to_iv3/report_inception_a1_5x5.txt        -n inception_a1_5x5
./fchksnr -t to_iv3/inception_a1_3x3_reduce_o.dat  -r tv_iv3/tv_inception_a1_3x3_reduce_relu_o.dat   -R to_iv3/report_inception_a1_3x3_reduce.txt -n inception_a1_3x3_reduce
./fchksnr -t to_iv3/inception_a1_3x3_1_o.dat       -r tv_iv3/tv_inception_a1_3x3_1_relu_o.dat        -R to_iv3/report_inception_a1_3x3_1.txt      -n inception_a1_3x3_1
./fchksnr -t to_iv3/inception_a1_3x3_2_o.dat       -r tv_iv3/tv_inception_a1_3x3_2_relu_o.dat        -R to_iv3/report_inception_a1_3x3_2.txt      -n inception_a1_3x3_2
./fchksnr -t to_iv3/inception_a1_pool_o.dat        -r tv_iv3/tv_inception_a1_pool_o.dat              -R to_iv3/report_inception_a1_pool.txt       -n inception_a1_pool
./fchksnr -t to_iv3/inception_a1_pool_proj_o.dat   -r tv_iv3/tv_inception_a1_pool_proj_relu_o.dat    -R to_iv3/report_inception_a1_pool_proj.txt  -n inception_a1_pool_proj
./fchksnr -t to_iv3/inception_a1_output_o.dat      -r tv_iv3/tv_inception_a1_output_o.dat            -R to_iv3/report_inception_a1_output.txt     -n inception_a1_output

./fchksnr -t to_iv3/inception_a2_1x1_o.dat         -r tv_iv3/tv_inception_a2_1x1_relu_o.dat          -R to_iv3/report_inception_a2_1x1.txt        -n inception_a2_1x1
./fchksnr -t to_iv3/inception_a2_5x5_reduce_o.dat  -r tv_iv3/tv_inception_a2_5x5_reduce_relu_o.dat   -R to_iv3/report_inception_a2_5x5_reduce.txt -n inception_a2_5x5_reduce
./fchksnr -t to_iv3/inception_a2_5x5_o.dat         -r tv_iv3/tv_inception_a2_5x5_relu_o.dat          -R to_iv3/report_inception_a2_5x5.txt        -n inception_a2_5x5
./fchksnr -t to_iv3/inception_a2_3x3_reduce_o.dat  -r tv_iv3/tv_inception_a2_3x3_reduce_relu_o.dat   -R to_iv3/report_inception_a2_3x3_reduce.txt -n inception_a2_3x3_reduce
./fchksnr -t to_iv3/inception_a2_3x3_1_o.dat       -r tv_iv3/tv_inception_a2_3x3_1_relu_o.dat        -R to_iv3/report_inception_a2_3x3_1.txt      -n inception_a2_3x3_1
./fchksnr -t to_iv3/inception_a2_3x3_2_o.dat       -r tv_iv3/tv_inception_a2_3x3_2_relu_o.dat        -R to_iv3/report_inception_a2_3x3_2.txt      -n inception_a2_3x3_2
./fchksnr -t to_iv3/inception_a2_pool_o.dat        -r tv_iv3/tv_inception_a2_pool_o.dat              -R to_iv3/report_inception_a2_pool.txt       -n inception_a2_pool
./fchksnr -t to_iv3/inception_a2_pool_proj_o.dat   -r tv_iv3/tv_inception_a2_pool_proj_relu_o.dat    -R to_iv3/report_inception_a2_pool_proj.txt  -n inception_a2_pool_proj
./fchksnr -t to_iv3/inception_a2_output_o.dat      -r tv_iv3/tv_inception_a2_output_o.dat            -R to_iv3/report_inception_a2_output.txt     -n inception_a2_output

./fchksnr -t to_iv3/inception_a3_1x1_o.dat         -r tv_iv3/tv_inception_a3_1x1_relu_o.dat          -R to_iv3/report_inception_a3_1x1.txt        -n inception_a3_1x1
./fchksnr -t to_iv3/inception_a3_5x5_reduce_o.dat  -r tv_iv3/tv_inception_a3_5x5_reduce_relu_o.dat   -R to_iv3/report_inception_a3_5x5_reduce.txt -n inception_a3_5x5_reduce
./fchksnr -t to_iv3/inception_a3_5x5_o.dat         -r tv_iv3/tv_inception_a3_5x5_relu_o.dat          -R to_iv3/report_inception_a3_5x5.txt        -n inception_a3_5x5
./fchksnr -t to_iv3/inception_a3_3x3_reduce_o.dat  -r tv_iv3/tv_inception_a3_3x3_reduce_relu_o.dat   -R to_iv3/report_inception_a3_3x3_reduce.txt -n inception_a3_3x3_reduce
./fchksnr -t to_iv3/inception_a3_3x3_1_o.dat       -r tv_iv3/tv_inception_a3_3x3_1_relu_o.dat        -R to_iv3/report_inception_a3_3x3_1.txt      -n inception_a3_3x3_1
./fchksnr -t to_iv3/inception_a3_3x3_2_o.dat       -r tv_iv3/tv_inception_a3_3x3_2_relu_o.dat        -R to_iv3/report_inception_a3_3x3_2.txt      -n inception_a3_3x3_2
./fchksnr -t to_iv3/inception_a3_pool_o.dat        -r tv_iv3/tv_inception_a3_pool_o.dat              -R to_iv3/report_inception_a3_pool.txt       -n inception_a3_pool
./fchksnr -t to_iv3/inception_a3_pool_proj_o.dat   -r tv_iv3/tv_inception_a3_pool_proj_relu_o.dat    -R to_iv3/report_inception_a3_pool_proj.txt  -n inception_a3_pool_proj
./fchksnr -t to_iv3/inception_a3_output_o.dat      -r tv_iv3/tv_inception_a3_output_o.dat            -R to_iv3/report_inception_a3_output.txt     -n inception_a3_output

./fchksnr -t to_iv3/reduction_a_3x3_o.dat          -r tv_iv3/tv_reduction_a_3x3_relu_o.dat           -R to_iv3/report_reduction_a_3x3.txt          -n reduction_a_3x3
./fchksnr -t to_iv3/reduction_a_3x3_2_reduce_o.dat -r tv_iv3/tv_reduction_a_3x3_2_reduce_relu_o.dat  -R to_iv3/report_reduction_a_3x3_2_reduce.txt -n reduction_a_3x3_2_reduce
./fchksnr -t to_iv3/reduction_a_3x3_2_o.dat        -r tv_iv3/tv_reduction_a_3x3_2_relu_o.dat         -R to_iv3/report_reduction_a_3x3_2.txt        -n reduction_a_3x3_2
./fchksnr -t to_iv3/reduction_a_3x3_3_o.dat        -r tv_iv3/tv_reduction_a_3x3_3_relu_o.dat         -R to_iv3/report_reduction_a_3x3_3.txt        -n reduction_a_3x3_3
./fchksnr -t to_iv3/reduction_a_pool_o.dat         -r tv_iv3/tv_reduction_a_pool_o.dat               -R to_iv3/report_reduction_a_pool.txt         -n reduction_a_pool
./fchksnr -t to_iv3/reduction_a_concat_o.dat       -r tv_iv3/tv_reduction_a_concat_o.dat             -R to_iv3/report_reduction_a_concat.txt       -n reduction_a_concat 

./fchksnr -t to_iv3/inception_b1_1x1_2_o.dat       -r tv_iv3/tv_inception_b1_1x1_2_relu_o.dat        -R to_iv3/report_inception_b1_1x1_2.txt      -n inception_b1_1x1_2
./fchksnr -t to_iv3/inception_b1_1x7_reduce_o.dat  -r tv_iv3/tv_inception_b1_1x7_reduce_relu_o.dat   -R to_iv3/report_inception_b1_1x7_reduce.txt -n inception_b1_1x7_reduce
./fchksnr -t to_iv3/inception_b1_1x7_o.dat         -r tv_iv3/tv_inception_b1_1x7_relu_o.dat          -R to_iv3/report_inception_b1_1x7.txt        -n inception_b1_1x7
./fchksnr -t to_iv3/inception_b1_7x1_o.dat         -r tv_iv3/tv_inception_b1_7x1_relu_o.dat          -R to_iv3/report_inception_b1_7x1.txt        -n inception_b1_7x1
./fchksnr -t to_iv3/inception_b1_7x1_reduce_o.dat  -r tv_iv3/tv_inception_b1_7x1_reduce_relu_o.dat   -R to_iv3/report_inception_b1_7x1_reduce.txt -n inception_b1_7x1_reduce
./fchksnr -t to_iv3/inception_b1_7x1_2_o.dat       -r tv_iv3/tv_inception_b1_7x1_2_relu_o.dat        -R to_iv3/report_inception_b1_7x1_2.txt      -n inception_b1_7x1_2
./fchksnr -t to_iv3/inception_b1_1x7_2_o.dat       -r tv_iv3/tv_inception_b1_1x7_2_relu_o.dat        -R to_iv3/report_inception_b1_1x7_2.txt      -n inception_b1_1x7_2
./fchksnr -t to_iv3/inception_b1_1x7_3_o.dat       -r tv_iv3/tv_inception_b1_1x7_3_relu_o.dat        -R to_iv3/report_inception_b1_1x7_3.txt      -n inception_b1_1x7_3
./fchksnr -t to_iv3/inception_b1_pool_ave_o.dat    -r tv_iv3/tv_inception_b1_pool_ave_o.dat          -R to_iv3/report_inception_b1_pool_ave.txt   -n inception_b1_pool_ave
./fchksnr -t to_iv3/inception_b1_1x1_o.dat         -r tv_iv3/tv_inception_b1_1x1_relu_o.dat          -R to_iv3/report_inception_b1_1x1.txt        -n inception_b1_1x1
./fchksnr -t to_iv3/inception_b1_concat_o.dat      -r tv_iv3/tv_inception_b1_concat_o.dat            -R to_iv3/report_inception_b1_concat.txt     -n inception_b1_concat

./fchksnr -t to_iv3/inception_b2_1x1_2_o.dat       -r tv_iv3/tv_inception_b2_1x1_2_relu_o.dat        -R to_iv3/report_inception_b2_1x1_2.txt      -n inception_b2_1x1_2
./fchksnr -t to_iv3/inception_b2_1x7_reduce_o.dat  -r tv_iv3/tv_inception_b2_1x7_reduce_relu_o.dat   -R to_iv3/report_inception_b2_1x7_reduce.txt -n inception_b2_1x7_reduce
./fchksnr -t to_iv3/inception_b2_1x7_o.dat         -r tv_iv3/tv_inception_b2_1x7_relu_o.dat          -R to_iv3/report_inception_b2_1x7.txt        -n inception_b2_1x7
./fchksnr -t to_iv3/inception_b2_7x1_o.dat         -r tv_iv3/tv_inception_b2_7x1_relu_o.dat          -R to_iv3/report_inception_b2_7x1.txt        -n inception_b2_7x1
./fchksnr -t to_iv3/inception_b2_7x1_reduce_o.dat  -r tv_iv3/tv_inception_b2_7x1_reduce_relu_o.dat   -R to_iv3/report_inception_b2_7x1_reduce.txt -n inception_b2_7x1_reduce
./fchksnr -t to_iv3/inception_b2_7x1_2_o.dat       -r tv_iv3/tv_inception_b2_7x1_2_relu_o.dat        -R to_iv3/report_inception_b2_7x1_2.txt      -n inception_b2_7x1_2
./fchksnr -t to_iv3/inception_b2_1x7_2_o.dat       -r tv_iv3/tv_inception_b2_1x7_2_relu_o.dat        -R to_iv3/report_inception_b2_1x7_2.txt      -n inception_b2_1x7_2
./fchksnr -t to_iv3/inception_b2_7x1_3_o.dat       -r tv_iv3/tv_inception_b2_7x1_3_relu_o.dat        -R to_iv3/report_inception_b2_7x1_3.txt      -n inception_b2_7x1_3
./fchksnr -t to_iv3/inception_b2_1x7_3_o.dat       -r tv_iv3/tv_inception_b2_1x7_3_relu_o.dat        -R to_iv3/report_inception_b2_1x7_3.txt      -n inception_b2_1x7_3
./fchksnr -t to_iv3/inception_b2_pool_ave_o.dat    -r tv_iv3/tv_inception_b2_pool_ave_o.dat          -R to_iv3/report_inception_b2_pool_ave.txt   -n inception_b2_pool_ave
./fchksnr -t to_iv3/inception_b2_1x1_o.dat         -r tv_iv3/tv_inception_b2_1x1_relu_o.dat          -R to_iv3/report_inception_b2_1x1.txt        -n inception_b2_1x1
./fchksnr -t to_iv3/inception_b2_concat_o.dat      -r tv_iv3/tv_inception_b2_concat_o.dat            -R to_iv3/report_inception_b2_concat.txt     -n inception_b2_concat

./fchksnr -t to_iv3/inception_b3_1x1_2_o.dat       -r tv_iv3/tv_inception_b3_1x1_2_relu_o.dat        -R to_iv3/report_inception_b3_1x1_2.txt      -n inception_b3_1x1_2
./fchksnr -t to_iv3/inception_b3_1x7_reduce_o.dat  -r tv_iv3/tv_inception_b3_1x7_reduce_relu_o.dat   -R to_iv3/report_inception_b3_1x7_reduce.txt -n inception_b3_1x7_reduce
./fchksnr -t to_iv3/inception_b3_1x7_o.dat         -r tv_iv3/tv_inception_b3_1x7_relu_o.dat          -R to_iv3/report_inception_b3_1x7.txt        -n inception_b3_1x7
./fchksnr -t to_iv3/inception_b3_7x1_o.dat         -r tv_iv3/tv_inception_b3_7x1_relu_o.dat          -R to_iv3/report_inception_b3_7x1.txt        -n inception_b3_7x1
./fchksnr -t to_iv3/inception_b3_7x1_reduce_o.dat  -r tv_iv3/tv_inception_b3_7x1_reduce_relu_o.dat   -R to_iv3/report_inception_b3_7x1_reduce.txt -n inception_b3_7x1_reduce
./fchksnr -t to_iv3/inception_b3_7x1_2_o.dat       -r tv_iv3/tv_inception_b3_7x1_2_relu_o.dat        -R to_iv3/report_inception_b3_7x1_2.txt      -n inception_b3_7x1_2
./fchksnr -t to_iv3/inception_b3_1x7_2_o.dat       -r tv_iv3/tv_inception_b3_1x7_2_relu_o.dat        -R to_iv3/report_inception_b3_1x7_2.txt      -n inception_b3_1x7_2
./fchksnr -t to_iv3/inception_b3_7x1_3_o.dat       -r tv_iv3/tv_inception_b3_7x1_3_relu_o.dat        -R to_iv3/report_inception_b3_7x1_3.txt      -n inception_b3_7x1_3
./fchksnr -t to_iv3/inception_b3_1x7_3_o.dat       -r tv_iv3/tv_inception_b3_1x7_3_relu_o.dat        -R to_iv3/report_inception_b3_1x7_3.txt      -n inception_b3_1x7_3
./fchksnr -t to_iv3/inception_b3_pool_ave_o.dat    -r tv_iv3/tv_inception_b3_pool_ave_o.dat          -R to_iv3/report_inception_b3_pool_ave.txt   -n inception_b3_pool_ave
./fchksnr -t to_iv3/inception_b3_1x1_o.dat         -r tv_iv3/tv_inception_b3_1x1_relu_o.dat          -R to_iv3/report_inception_b3_1x1.txt        -n inception_b3_1x1
./fchksnr -t to_iv3/inception_b3_concat_o.dat      -r tv_iv3/tv_inception_b3_concat_o.dat            -R to_iv3/report_inception_b3_concat.txt     -n inception_b3_concat

./fchksnr -t to_iv3/inception_b4_1x1_2_o.dat       -r tv_iv3/tv_inception_b4_1x1_2_relu_o.dat        -R to_iv3/report_inception_b4_1x1_2.txt      -n inception_b4_1x1_2
./fchksnr -t to_iv3/inception_b4_1x7_reduce_o.dat  -r tv_iv3/tv_inception_b4_1x7_reduce_relu_o.dat   -R to_iv3/report_inception_b4_1x7_reduce.txt -n inception_b4_1x7_reduce
./fchksnr -t to_iv3/inception_b4_1x7_o.dat         -r tv_iv3/tv_inception_b4_1x7_relu_o.dat          -R to_iv3/report_inception_b4_1x7.txt        -n inception_b4_1x7
./fchksnr -t to_iv3/inception_b4_7x1_o.dat         -r tv_iv3/tv_inception_b4_7x1_relu_o.dat          -R to_iv3/report_inception_b4_7x1.txt        -n inception_b4_7x1
./fchksnr -t to_iv3/inception_b4_7x1_reduce_o.dat  -r tv_iv3/tv_inception_b4_7x1_reduce_relu_o.dat   -R to_iv3/report_inception_b4_7x1_reduce.txt -n inception_b4_7x1_reduce
./fchksnr -t to_iv3/inception_b4_7x1_2_o.dat       -r tv_iv3/tv_inception_b4_7x1_2_relu_o.dat        -R to_iv3/report_inception_b4_7x1_2.txt      -n inception_b4_7x1_2
./fchksnr -t to_iv3/inception_b4_1x7_2_o.dat       -r tv_iv3/tv_inception_b4_1x7_2_relu_o.dat        -R to_iv3/report_inception_b4_1x7_2.txt      -n inception_b4_1x7_2
./fchksnr -t to_iv3/inception_b4_7x1_3_o.dat       -r tv_iv3/tv_inception_b4_7x1_3_relu_o.dat        -R to_iv3/report_inception_b4_7x1_3.txt      -n inception_b4_7x1_3
./fchksnr -t to_iv3/inception_b4_1x7_3_o.dat       -r tv_iv3/tv_inception_b4_1x7_3_relu_o.dat        -R to_iv3/report_inception_b4_1x7_3.txt      -n inception_b4_1x7_3
./fchksnr -t to_iv3/inception_b4_pool_ave_o.dat    -r tv_iv3/tv_inception_b4_pool_ave_o.dat          -R to_iv3/report_inception_b4_pool_ave.txt   -n inception_b4_pool_ave
./fchksnr -t to_iv3/inception_b4_1x1_o.dat         -r tv_iv3/tv_inception_b4_1x1_relu_o.dat          -R to_iv3/report_inception_b4_1x1.txt        -n inception_b4_1x1
./fchksnr -t to_iv3/inception_b4_concat_o.dat      -r tv_iv3/tv_inception_b4_concat_o.dat            -R to_iv3/report_inception_b4_concat.txt     -n inception_b4_concat

./fchksnr -t to_iv3/reduction_b_3x3_reduce_o.dat   -r tv_iv3/tv_reduction_b_3x3_reduce_relu_o.dat    -R to_iv3/report_reduction_b_3x3_reduce.txt   -n reduction_b_3x3_reduce
./fchksnr -t to_iv3/reduction_b_3x3_o.dat          -r tv_iv3/tv_reduction_b_3x3_relu_o.dat           -R to_iv3/report_reduction_b_3x3.txt          -n reduction_b_3x3
./fchksnr -t to_iv3/reduction_b_1x7_reduce_o.dat   -r tv_iv3/tv_reduction_b_1x7_reduce_relu_o.dat    -R to_iv3/report_reduction_b_1x7_reduce.txt   -n reduction_b_1x7_reduce
./fchksnr -t to_iv3/reduction_b_1x7_o.dat          -r tv_iv3/tv_reduction_b_1x7_relu_o.dat           -R to_iv3/report_reduction_b_1x7.txt          -n reduction_b_1x7
./fchksnr -t to_iv3/reduction_b_7x1_o.dat          -r tv_iv3/tv_reduction_b_7x1_relu_o.dat           -R to_iv3/report_reduction_b_7x1.txt          -n reduction_b_7x1
./fchksnr -t to_iv3/reduction_b_3x3_2_o.dat        -r tv_iv3/tv_reduction_b_3x3_2_relu_o.dat         -R to_iv3/report_reduction_b_3x3_2.txt        -n reduction_b_3x3_2
./fchksnr -t to_iv3/reduction_b_pool_o.dat         -r tv_iv3/tv_reduction_b_pool_o.dat               -R to_iv3/report_reduction_b_pool.txt         -n reduction_b_pool
./fchksnr -t to_iv3/reduction_b_concat_o.dat       -r tv_iv3/tv_reduction_b_concat_o.dat             -R to_iv3/report_reduction_b_concat.txt       -n reduction_b_concat

./fchksnr -t to_iv3/inception_c1_1x1_2_o.dat       -r tv_iv3/tv_inception_c1_1x1_2_relu_o.dat        -R to_iv3/report_inception_c1_1x1_2.txt      -n inception_c1_1x1_2
./fchksnr -t to_iv3/inception_c1_1x3_reduce_o.dat  -r tv_iv3/tv_inception_c1_1x3_reduce_relu_o.dat   -R to_iv3/report_inception_c1_1x3_reduce.txt -n inception_c1_1x3_reduce
./fchksnr -t to_iv3/inception_c1_1x3_o.dat         -r tv_iv3/tv_inception_c1_1x3_relu_o.dat          -R to_iv3/report_inception_c1_1x3.txt        -n inception_c1_1x3
./fchksnr -t to_iv3/inception_c1_3x1_o.dat         -r tv_iv3/tv_inception_c1_3x1_relu_o.dat          -R to_iv3/report_inception_c1_3x1.txt        -n inception_c1_3x1
./fchksnr -t to_iv3/inception_c1_3x3_reduce_o.dat  -r tv_iv3/tv_inception_c1_3x3_reduce_relu_o.dat   -R to_iv3/report_inception_c1_3x3_reduce.txt -n inception_c1_3x3_reduce
./fchksnr -t to_iv3/inception_c1_3x3_o.dat         -r tv_iv3/tv_inception_c1_3x3_relu_o.dat          -R to_iv3/report_inception_c1_3x3.txt        -n inception_c1_3x3
./fchksnr -t to_iv3/inception_c1_1x3_2_o.dat       -r tv_iv3/tv_inception_c1_1x3_2_relu_o.dat        -R to_iv3/report_inception_c1_1x3_2.txt      -n inception_c1_1x3_2
./fchksnr -t to_iv3/inception_c1_3x1_2_o.dat       -r tv_iv3/tv_inception_c1_3x1_2_relu_o.dat        -R to_iv3/report_inception_c1_3x1_2.txt      -n inception_c1_3x1_2
./fchksnr -t to_iv3/inception_c1_pool_o.dat        -r tv_iv3/tv_inception_c1_pool_o.dat              -R to_iv3/report_inception_c1_pool.txt       -n inception_c1_pool
./fchksnr -t to_iv3/inception_c1_1x1_o.dat         -r tv_iv3/tv_inception_c1_1x1_relu_o.dat          -R to_iv3/report_inception_c1_1x1.txt        -n inception_c1_1x1
./fchksnr -t to_iv3/inception_c1_concat_o.dat      -r tv_iv3/tv_inception_c1_concat_o.dat            -R to_iv3/report_inception_c1_concat.txt     -n inception_c1_concat

./fchksnr -t to_iv3/inception_c2_1x1_2_o.dat       -r tv_iv3/tv_inception_c2_1x1_2_relu_o.dat        -R to_iv3/report_inception_c2_1x1_2.txt      -n inception_c2_1x1_2
./fchksnr -t to_iv3/inception_c2_1x3_reduce_o.dat  -r tv_iv3/tv_inception_c2_1x3_reduce_relu_o.dat   -R to_iv3/report_inception_c2_1x3_reduce.txt -n inception_c2_1x3_reduce
./fchksnr -t to_iv3/inception_c2_1x3_o.dat         -r tv_iv3/tv_inception_c2_1x3_relu_o.dat          -R to_iv3/report_inception_c2_1x3.txt        -n inception_c2_1x3
./fchksnr -t to_iv3/inception_c2_3x1_o.dat         -r tv_iv3/tv_inception_c2_3x1_relu_o.dat          -R to_iv3/report_inception_c2_3x1.txt        -n inception_c2_3x1
./fchksnr -t to_iv3/inception_c2_3x3_reduce_o.dat  -r tv_iv3/tv_inception_c2_3x3_reduce_relu_o.dat   -R to_iv3/report_inception_c2_3x3_reduce.txt -n inception_c2_3x3_reduce
./fchksnr -t to_iv3/inception_c2_3x3_o.dat         -r tv_iv3/tv_inception_c2_3x3_relu_o.dat          -R to_iv3/report_inception_c2_3x3.txt        -n inception_c2_3x3
./fchksnr -t to_iv3/inception_c2_1x3_2_o.dat       -r tv_iv3/tv_inception_c2_1x3_2_relu_o.dat        -R to_iv3/report_inception_c2_1x3_2.txt      -n inception_c2_1x3_2
./fchksnr -t to_iv3/inception_c2_3x1_2_o.dat       -r tv_iv3/tv_inception_c2_3x1_2_relu_o.dat        -R to_iv3/report_inception_c2_3x1_2.txt      -n inception_c2_3x1_2
./fchksnr -t to_iv3/inception_c2_pool_o.dat        -r tv_iv3/tv_inception_c2_pool_o.dat              -R to_iv3/report_inception_c2_pool.txt       -n inception_c2_pool
./fchksnr -t to_iv3/inception_c2_1x1_o.dat         -r tv_iv3/tv_inception_c2_1x1_relu_o.dat          -R to_iv3/report_inception_c2_1x1.txt        -n inception_c2_1x1
./fchksnr -t to_iv3/inception_c2_concat_o.dat      -r tv_iv3/tv_inception_c2_concat_o.dat            -R to_iv3/report_inception_c2_concat.txt     -n inception_c2_concat

./fchksnr -t to_iv3/pool_8x8_s1_o.dat              -r tv_iv3/tv_pool_8x8_s1_o.dat                    -R to_iv3/report_pool_8x8_s1.txt             -n pool_8x8_s1
./fchksnr -t to_iv3/classifier_o.dat               -r tv_iv3/tv_classifier_o.dat                     -R to_iv3/report_classifier.txt              -n classifier
./fchksnr -t to_iv3/prob_o.dat                     -r tv_iv3/tv_prob_o.dat                           -R to_iv3/report_prob.txt                    -n prob


echo "/*---------------------------------------------------------------------------*" >  rpt_iv3.txt
echo " * NN GRAPH ACCURACY CHECK REPORT                                            *" >> rpt_iv3.txt
grep Final  to_iv3/report_conv1_3x3_s2_i.txt                   >> rpt_iv3.txt 
grep Final  to_iv3/report_conv1_3x3_s2.txt                     >> rpt_iv3.txt 
grep Final  to_iv3/report_conv2_3x3_s1.txt                     >> rpt_iv3.txt 
grep Final  to_iv3/report_conv3_3x3_s1.txt                     >> rpt_iv3.txt 
grep Final  to_iv3/report_pool1_3x3_s2.txt                     >> rpt_iv3.txt 
grep Final  to_iv3/report_conv4_3x3_reduce.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_conv4_3x3.txt                        >> rpt_iv3.txt 
grep Final  to_iv3/report_pool2_3x3_s2.txt                     >> rpt_iv3.txt 

grep Final  to_iv3/report_inception_a1_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a1_5x5_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a1_5x5.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a1_3x3_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a1_3x3_1.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a1_3x3_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a1_pool.txt                >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a1_pool_proj.txt           >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a1_output.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_inception_a2_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a2_5x5_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a2_5x5.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a2_3x3_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a2_3x3_1.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a2_3x3_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a2_pool.txt                >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a2_pool_proj.txt           >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a2_output.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_inception_a3_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a3_5x5_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a3_5x5.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a3_3x3_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a3_3x3_1.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a3_3x3_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a3_pool.txt                >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a3_pool_proj.txt           >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_a3_output.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_reduction_a_3x3.txt                   >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_a_3x3_2_reduce.txt          >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_a_3x3_2.txt                 >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_a_3x3_3.txt                 >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_a_pool.txt                  >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_a_concat.txt                >> rpt_iv3.txt

grep Final  to_iv3/report_inception_b1_1x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_1x7_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_1x7.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_7x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_7x1_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_7x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_1x7_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_1x7_3.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_pool_ave.txt            >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b1_concat.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_inception_b2_1x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_1x7_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_1x7.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_7x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_7x1_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_7x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_1x7_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_7x1_3.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_1x7_3.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_pool_ave.txt            >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b2_concat.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_inception_b3_1x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_1x7_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_1x7.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_7x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_7x1_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_7x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_1x7_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_7x1_3.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_1x7_3.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_pool_ave.txt            >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b3_concat.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_inception_b4_1x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_1x7_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_1x7.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_7x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_7x1_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_7x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_1x7_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_7x1_3.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_1x7_3.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_pool_ave.txt            >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_b4_concat.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_reduction_b_3x3_reduce.txt            >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_b_3x3.txt                   >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_b_1x7_reduce.txt            >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_b_1x7.txt                   >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_b_7x1.txt                   >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_b_3x3_2.txt                 >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_b_pool.txt                  >> rpt_iv3.txt
grep Final  to_iv3/report_reduction_b_concat.txt                >> rpt_iv3.txt

grep Final  to_iv3/report_inception_c1_1x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_1x3_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_1x3.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_3x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_3x3_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_3x3.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_1x3_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_3x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_pool.txt                >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c1_concat.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_inception_c2_1x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_1x3_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_1x3.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_3x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_3x3_reduce.txt          >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_3x3.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_1x3_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_3x1_2.txt               >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_pool.txt                >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_1x1.txt                 >> rpt_iv3.txt 
grep Final  to_iv3/report_inception_c2_concat.txt              >> rpt_iv3.txt 

grep Final  to_iv3/report_pool_8x8_s1.txt                      >> rpt_iv3.txt 
grep Final  to_iv3/report_classifier.txt                       >> rpt_iv3.txt 
grep Final  to_iv3/report_prob.txt                             >> rpt_iv3.txt 
echo " *---------------------------------------------------------------------------*/" >> rpt_iv3.txt

#more rpt_iv3.txt
