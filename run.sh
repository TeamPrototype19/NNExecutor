mkdir -p test
#gdb --args ./nne -p nnc.cgo -i input.dat -o output.dat
            ./nne -p nnc.cgo -i input.dat -o output.dat

mv conv*.dat data*.dat ip*.dat pool*.dat relu*.dat prob*.dat test
