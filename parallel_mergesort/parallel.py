# Global interpreter lock -> 0 multi-threads but multi-processes
import multiprocessing as mp
import time
import numpy as np


# 4 cores
NUM_PROCESS = 4

# Global variables
n = 0
my_list = []


# Merge two parts into one
def merge(arr, low, mid, high):
    if high <= low:
        return

    # Initialize
    left_part = arr[low:mid + 1].copy()
    right_part = arr[mid + 1:high + 1].copy()

    left_size, right_size = len(left_part), len(right_part)
    i = j = 0
    cc = low

    # O(left_size + right_size) complexity algorithm
    while i < left_size and j < right_size:
        if left_part[i] <= right_part[j]:
            arr[cc] = left_part[i]
            i += 1
        else:
            arr[cc] = right_part[j]
            j += 1
        cc += 1

    while i < left_size:
        arr[cc] = left_part[i]
        i += 1
        cc += 1

    while j < right_size:
        arr[cc] = right_part[j]
        j += 1
        cc += 1

    return arr

def merge_sort(arr, low, high, q, step):
    if low >= high:
        if step == 0 and low == high:
            q.put(arr[low])
        return

    if low == high - 1:
        if arr[low] > arr[high]:
            arr[low], arr[high] = arr[high], arr[low]

            if step == 0:
                q.put(arr[low])
                q.put(arr[high])
        return

    mid = (low + high) // 2

    merge_sort(arr, low, mid, q, step + 1)
    merge_sort(arr, mid + 1, high, q, step + 1)

    arr = merge(arr, low, mid, high)
    if step == 0:
        for i in range(low, high + 1):
            q.put(arr[i])

def convert_to_array(queue):
    arr = []
    while queue.empty() is False:
        arr.append(queue.get())
    return arr

def parallel_mergesort():
    distance = n // NUM_PROCESS
    p = []
    q = []
    global my_list

    # Create NUM_PROCESS processes
    for i in range(NUM_PROCESS - 1):
        q.append(mp.Queue())
        p.append(mp.Process(target=merge_sort, args=(my_list, i * distance, (i + 1) * distance - 1, q[i], 0)))
        p[i].start()
        p[i].join()
    q.append(mp.Queue())
    p.append(mp.Process(target=merge_sort, args=(my_list, (NUM_PROCESS - 1) * distance, n-1, q[NUM_PROCESS - 1], 0)))
    p[NUM_PROCESS - 1].start()
    p[NUM_PROCESS - 1].join()

    # merge results of all processes
    for i in range(NUM_PROCESS - 1):
        my_list[i * distance:(i + 1) * distance] = convert_to_array(q[i])
    my_list[(i + 1) * distance:n] = convert_to_array(q[NUM_PROCESS - 1])

    for i in range(1, NUM_PROCESS - 1):
        my_list = merge(arr=my_list, low=0, mid=i*distance - 1, high=(i+1)*distance - 1)
    my_list = merge(arr=my_list, low=0, mid=(NUM_PROCESS - 1)*distance - 1, high=n-1)


if __name__ == '__main__':
    # Input
    print('Parallel Merge Sort')
    print("Enter array's length: ", end='')
    n = int(input())
    print("Enter array's element: ", end='')
    # my_list = list(map(int, input().split()))
    my_list = np.random()

    # Parallel sort
    start = time.time()
    parallel_mergesort()
    end = time.time()

    print("Sorted list:", my_list)
    print(f'Sorting time: {end - start} seconds')
