./fchksnr -t test/conv1_o.dat -r tv/tv_conv1_o.dat -R test/report_conv1.txt
./fchksnr -t test/pool1_o.dat -r tv/tv_pool1_o.dat -R test/report_pool1.txt
./fchksnr -t test/conv2_o.dat -r tv/tv_conv2_o.dat -R test/report_conv2.txt
./fchksnr -t test/pool2_o.dat -r tv/tv_pool2_o.dat -R test/report_pool2.txt
./fchksnr -t test/ip1_o.dat   -r tv/tv_ip1_o.dat   -R test/report_ip1.txt
./fchksnr -t test/relu1_o.dat -r tv/tv_relu1_o.dat -R test/report_relu1.txt
./fchksnr -t test/ip2_o.dat   -r tv/tv_ip2_o.dat   -R test/report_ip2.txt
./fchksnr -t test/prob_o.dat  -r tv/tv_loss_o.dat  -R test/report_prob.txt

echo "/*---------------------------------------------*" >  reportA.txt
echo " * NN GRAPH ACCURACY CHECK REPORT              *" >> reportA.txt
grep Final test/report_conv1.txt                        >> reportA.txt
grep Final test/report_pool1.txt                        >> reportA.txt
grep Final test/report_conv2.txt                        >> reportA.txt
grep Final test/report_pool2.txt                        >> reportA.txt
grep Final test/report_ip1.txt                          >> reportA.txt
grep Final test/report_relu1.txt                        >> reportA.txt
grep Final test/report_ip2.txt                          >> reportA.txt
grep Final test/report_prob.txt                         >> reportA.txt
echo "/*---------------------------------------------*" >> reportA.txt

more reportA.txt
