import numpy as np
import os
import math
from numpy.random import randint



TEST_DIR = "modulo"



def solve(t,a,b,c):
    a = int(a)
    b = int(b)
    c = int(c)
    if t == 1:
        return a*b%c
    else:
        if b > c:
            b,c = c,b
        
        x = a//math.lcm(b,c)
        res = x*b + b - 1

        if a%b == a%c:
            res = res - (b - 1 - a%b)
        
        return res



def makedir(test_id):
    test_id = str(test_id)
    if not os.path.isdir(TEST_DIR + "/test" + test_id):
        os.mkdir(TEST_DIR + "/test" + test_id)
    
    fi = open(TEST_DIR + "/test"+ test_id + "/modulo.inp","w")
    fo = open(TEST_DIR + "/test"+ test_id + "/modulo.out","w")
    return fi,fo



def subtask1(start,end):
    for test_id in range(start,end+1):
        fi,fo = makedir(test_id)

        q = randint(int(1e5)-1)+2
        fi.write(str(q)+'\n')

        t = 1
        a = int(1e9)
        b = int(1e9)
        c = int(1e9)
        fi.write('1 '+ str(a) +' '+ str(b) +' '+ str(c) +'\n')
        fo.write(str(solve(t,a,b,c))+'\n')

        t = 1
        a = 1
        b = 1
        c = 1
        fi.write('1 '+ str(a) +' '+ str(b) +' '+ str(c) +'\n')
        fo.write(str(solve(t,a,b,c))+'\n')

        for _ in range(q-2):

            t = 1
            a = randint(int(1e9))+1
            b = randint(int(1e9))+1
            c = randint(int(1e9))+1

            fi.write(str(t)+' '+str(a)+' '+str(b)+' '+str(c)+'\n')
            result = solve(t,a,b,c)
            fo.write(str(result)+'\n')

            

def subtask2(start,end):
    for test_id in range(start,end+1):
        fi,fo = makedir(test_id)

        q = randint(int(1e3)-1)+2
        fi.write(str(q)+'\n')

        t = 2
        a = int(1e4)
        b = int(1e2)
        c = int(1e2)
        fi.write(str(t)+' '+ str(a) +' '+ str(b) +' '+ str(c) +'\n')
        fo.write(str(solve(t,a,b,c))+'\n')

        t = 2
        a = 1
        b = 1
        c = 1
        fi.write(str(t)+' '+ str(a) +' '+ str(b) +' '+ str(c) +'\n')
        fo.write(str(solve(t,a,b,c))+'\n')


        for _ in range(q-2):

            t = 2
            a = randint(int(1e4))+1
            bound = min(a,100)
            b = randint(bound)+1
            c = randint(bound)+1

            fi.write(str(t)+' '+str(a)+' '+str(b)+' '+str(c)+'\n')
            result = solve(t,a,b,c)
            fo.write(str(result)+'\n')
            


def subtask3(start,end):
    for test_id in range(start,end+1):
        fi,fo = makedir(test_id)

        q = randint(int(1e5)-1)+2
        fi.write(str(q)+'\n')

        t = randint(2)+1
        a = int(1e9)
        b = int(1e5)
        c = int(1e5)
        fi.write(str(t)+' '+ str(a) +' '+ str(b) +' '+ str(c) +'\n')
        fo.write(str(solve(t,a,b,c))+'\n')


        t = randint(2)+1
        a = 1
        b = 1
        c = 1
        fi.write(str(t)+' '+ str(a) +' '+ str(b) +' '+ str(c) +'\n')
        fo.write(str(solve(t,a,b,c))+'\n')


        for _ in range(q-2):

            t = randint(2)+1
            a = randint(int(1e9))+1
            bound = min(a,int(1e5))
            b = randint(bound)+1
            c = randint(bound)+1

            fi.write(str(t)+' '+str(a)+' '+str(b)+' '+str(c)+'\n')
            result = solve(t,a,b,c)
            fo.write(str(result)+'\n')
            


def subtask4(start,end):
    for test_id in range(start,end+1):
        fi,fo = makedir(test_id)

        q = randint(int(1e5)-1)+2
        fi.write(str(q)+'\n')

        t = randint(2)+1
        a = int(1e18)
        b = int(1e12)
        c = int(1e12)
        fi.write(str(t)+' '+ str(a) +' '+ str(b) +' '+ str(c) +'\n')
        fo.write(str(solve(t,a,b,c))+'\n')


        t = randint(2)+1
        a = 1
        b = 1
        c = 1
        fi.write(str(t)+' '+ str(a) +' '+ str(b) +' '+ str(c) +'\n')
        fo.write(str(solve(t,a,b,c))+'\n')

        for _ in range(q-2):

            t = randint(2)+1
            a = randint(np.longlong(1e18),dtype=np.longlong)+1
            bound = min(a,np.longlong(1e12))
            b = randint(bound,dtype=np.longlong)+1
            c = randint(bound,dtype=np.longlong)+1
            
            fi.write(str(t)+' '+str(a)+' '+str(b)+' '+str(c)+'\n')
            result = solve(t,a,b,c)
            fo.write(str(result)+'\n')



# Create directory
if not os.path.isdir(TEST_DIR):
    os.mkdir(TEST_DIR)

subtask1(1,8)#20%
subtask2(9,16)#20%
subtask3(17,24)#20%
subtask4(25,40)#40%
