import numpy as np


SIZE = 2000
LOW = 0
HIGH = 1000

arr = np.random.randint(low=LOW, high=HIGH, size=SIZE)

with open('test.inp', mode='w') as f:
    for ele in arr:
        f.write(str(ele) + ' ')