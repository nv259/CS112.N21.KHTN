import numpy as np
import time

def merge(arr1,arr2):
    res = []
    i = 0
    j = 0
    while (i < len(arr1) and j < len(arr2)):
        if arr1[i] < arr2[j]:
            res.append(arr1[i])
            i+=1
        else:
            res.append(arr2[j])
            j+=1
    
    while i < len(arr1):
        res.append(arr1[i])
        i+=1
    
    while j < len(arr2):
        res.append(arr2[j])
        j+=1
    
    return res


def merge_sort(arr):
    length = len(arr)
    if (length == 1):
        return arr
    
    leftarr = merge_sort(arr[0:length//2])
    rightarr = merge_sort(arr[length//2:length])

    return merge(leftarr,rightarr)



lst = []

# Input
# try:
#     print('Merge Sort')
#     print("Enter array's element: ")
#
#     while True:
#         lst.append(int(input()))
# except:
with open('test.inp', 'r') as f:
    lst = list(map(int, f.read().split()))
    n = len(lst)

# Merge sort
start = time.time()
lst = merge_sort(lst)
end = time.time()


# Result
print("Sorted list: ",lst)
print(f'Sorting time: {end - start} seconds')
