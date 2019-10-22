mkdir -p to_mnist
#gdb --args ./nne -p nn_mnist.cgo -i tv_mnist/tv_conv1_i.dat -o out_mnist.dat
            ./nne -p nn_mnist.cgo -i tv_mnist/tv_conv1_i.dat -o out_mnist.dat

mv conv*.dat data*.dat ip*.dat pool*.dat relu*.dat prob*.dat to_mnist
