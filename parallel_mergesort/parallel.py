# Global interpreter lock -> 0 multi-threads but multi-processes
import multiprocessing as mp
import time


# 4 cores
MAX_PROCESS = 4

# Global variables
n = 0
my_list = []


# Merge two parts into one
def merge(arr, low, mid, high):
    if high <= low:
        return

    result = []
    i = low
    j = mid + 1

    while i <= mid and j <= high:
        if arr[i] < arr[j]:
            result.append(arr[i])
            i = i + 1
        else:
            result.append(arr[j])
            j = j + 1

    while i <= mid:
        result.append(arr[i])
        i = i + 1

    while j <= high:
        result.append(arr[j])
        j = j + 1

    return result

NUM_PROCESS
def parallel_merge_sort(arr, low, high):
    Split array into NUM_PROCESS subarrays (each contains about n // NUM_PROCESS elements)

    Create NUM_PROCESS processes (each handles one subarray)

    for process in processes:
        process.start()

    for process in processes:
        process.join()

    # Q is array of multiprocessing Queue (return array of each processes)
    for q in Q:
        result = merge(result, q)

    return result
end


def merge_sort(arr, low, high, q, step):
    if low >= high:
        if step == 0 and low == high:
            q.put([arr[low]])
        return

    if low == high - 1:
        if arr[low] > arr[high]:
            arr[low], arr[high] = arr[high], arr[low]

            if step == 0:
                q.put(arr[low:high+1])
        return

    mid = (low + high) // 2

    merge_sort(arr, low, mid, q, step + 1)
    merge_sort(arr, mid + 1, high, q, step + 1)

    arr[low:high + 1] = merge(arr, low, mid, high)
    if step == 0:
        q.put(arr[low:high+1])


def parallel_mergesort():
    NUM_PROCESS = min(MAX_PROCESS,n)
    distance = n // NUM_PROCESS
    p = []
    q = []
    global my_list

    # Create NUM_PROCESS processes
    for i in range(NUM_PROCESS - 1):
        q.append(mp.Queue())
        p.append(mp.Process(target=merge_sort, args=(my_list, i * distance, (i + 1) * distance - 1, q[i], 0)))
        p[i].start()
    q.append(mp.Queue())
    p.append(mp.Process(target=merge_sort, args=(my_list, (NUM_PROCESS - 1) * distance, n-1, q[NUM_PROCESS - 1], 0)))
    p[NUM_PROCESS - 1].start()


    # merge results of all processes
    for i in range(NUM_PROCESS - 1):
        my_list[i * distance:(i + 1) * distance] = q[i].get()
    my_list[(i + 1) * distance:n] = q[NUM_PROCESS - 1].get()

    for i in range(1, NUM_PROCESS - 1):
        my_list[0:(i + 1) * distance] = merge(arr=my_list, low=0, mid=i*distance - 1, high=(i+1)*distance - 1)
    my_list[0:n] = merge(arr=my_list, low=0, mid=(NUM_PROCESS - 1)*distance - 1, high=n-1)


if __name__ == '__main__':
    # Input
    print('Parallel Merge Sort')
    print("Enter array's length: ", end='')
    n = int(input())
    print("Enter array's element: ", end='')
    my_list = list(map(int, input().split()))
    
    # # Test
    #with open('test.inp', 'r') as f:
    #    my_list = list(map(int, f.read().split()))
    #    n = len(my_list)

    # Parallel sort
    start = time.time()
    parallel_mergesort()
    end = time.time()

    print("Sorted list:", my_list)
    print(f'Sorting time: {end - start} seconds')
