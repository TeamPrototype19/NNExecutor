./fchksnr -t to_mnist/conv1_o.dat -r tv_mnist/tv_conv1_o.dat -R to_mnist/report_conv1.txt
./fchksnr -t to_mnist/pool1_o.dat -r tv_mnist/tv_pool1_o.dat -R to_mnist/report_pool1.txt
./fchksnr -t to_mnist/conv2_o.dat -r tv_mnist/tv_conv2_o.dat -R to_mnist/report_conv2.txt
./fchksnr -t to_mnist/pool2_o.dat -r tv_mnist/tv_pool2_o.dat -R to_mnist/report_pool2.txt
./fchksnr -t to_mnist/ip1_o.dat   -r tv_mnist/tv_ip1_o.dat   -R to_mnist/report_ip1.txt
./fchksnr -t to_mnist/relu1_o.dat -r tv_mnist/tv_relu1_o.dat -R to_mnist/report_relu1.txt
./fchksnr -t to_mnist/ip2_o.dat   -r tv_mnist/tv_ip2_o.dat   -R to_mnist/report_ip2.txt
./fchksnr -t to_mnist/prob_o.dat  -r tv_mnist/tv_loss_o.dat  -R to_mnist/report_prob.txt

echo "/*---------------------------------------------------------------------------*" >  rpt_mnist.txt
echo " * NN GRAPH ACCURACY CHECK REPORT                                            *" >> rpt_mnist.txt
grep Final to_mnist/report_conv1.txt                    >> rpt_mnist.txt
grep Final to_mnist/report_pool1.txt                    >> rpt_mnist.txt
grep Final to_mnist/report_conv2.txt                    >> rpt_mnist.txt
grep Final to_mnist/report_pool2.txt                    >> rpt_mnist.txt
grep Final to_mnist/report_ip1.txt                      >> rpt_mnist.txt
grep Final to_mnist/report_relu1.txt                    >> rpt_mnist.txt
grep Final to_mnist/report_ip2.txt                      >> rpt_mnist.txt
grep Final to_mnist/report_prob.txt                     >> rpt_mnist.txt
echo " *---------------------------------------------------------------------------*/" >> rpt_mnist.txt

more rpt_mnist.txt
