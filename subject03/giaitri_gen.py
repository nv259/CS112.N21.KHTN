import numpy as np
import os
from numpy.random import randint


TEST_NUM = 20
TEST_DIR = "giaitri"


def solve(a,b):
    return pow(a,b) + pow(b,a)


def generate(test_id):
    if not os.path.isdir(TEST_DIR + "/test" + test_id):
        os.mkdir(TEST_DIR + "/test" + test_id)
    
    fi = open(TEST_DIR + "/test"+ test_id + "/giaitri.inp","w")
    fo = open(TEST_DIR + "/test"+ test_id + "/giaitri.out","w")

    t = randint(200)+1
    fi.write(str(t)+'\n')

    #edge case
    fi.write('1000 1000\n')
    fo.write(str(solve(1000,1000)) + '\n')
    
    for _ in range(t-1):
        a = randint(1000)+1
        b = randint(1000)+1
        fi.write(str(a) + ' ' + str(b) + '\n')

        result = solve(a,b)
        fo.write(str(result)+'\n')


# Create directory
if not os.path.isdir(TEST_DIR):
    os.mkdir(TEST_DIR)

for i in range(TEST_NUM):
    generate(str(i+1))
