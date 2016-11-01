# Lab 5: Multithreaded Matrix Multiplication

To generate Matrix **A** (say 3x2) using **print_rand_matrix**:  
'''  
$ ./print_rand_matrix -r 3 -c 2 > a_matrix_file.txt
'''

To generate Matrix **B** (say 2x3) using **print_rand_matrix**:  
'''  
$ ./print_rand_matrix -r 2 -c 3 > b_matrix_file.txt  
'''

To generate **product matrix** using *multithreaded (say 3 threads) matrix multiplication* through **my_matrix_multiply.c**:  
'''  
$ gcc my_matrix_multiply.c -o my_matrix_multiply  
$ ./my_matrix_multiply -a a_matrix_file.txt -b b_matrix_file.txt -t 3  
'''
