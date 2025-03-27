
def bubble_sort(arr):
    """"
    sorts using bubbling in O(n^2)
    """
    n = len(arr)
    j = n - 1
    while j >= 0:
        for i in range(j):
            if arr[i] > arr[i + 1]:
                tmp = arr[i]
                arr[i] = arr[i + 1]
                arr[i + 1] = tmp
        j = j - 1
    return arr

def insert_sort(arr):
    n = len(arr)
    sorted_arr = [0] * n
    for i in range(n):
        sorted_arr[i] = arr[i]
        for j in range(i):
            if sorted_arr[i - j] < sorted_arr[i - j - 1]:
                tmp =  sorted_arr[i - j]
                sorted_arr[i - j] = sorted_arr[i - j - 1]
                sorted_arr[i - j - 1] = tmp
            else:
                break
    return sorted_arr


def merge(left, right):
    n_l = len(left)
    n_r = len(right)
    i, j = 0, 0
    arr = []

    while i < n_l and j < n_r:
        if left[i] > right[j]:
            arr.append(right[j])
            j += 1
        else:
            arr.append(left[i])
            i += 1
    arr.extend(left[i:])
    arr.extend(right[j:])

    return arr

def merge_sort(arr):
    n = len(arr)
    if n <= 1:
        return arr
    m = n // 2
    right = merge_sort(arr[m:])
    left = merge_sort(arr[:m])

    return merge(left, right)


if __name__ == "__main__":
    arr = [9, 10, 8, 71, 90, 100, 5, 81]
    print(insert_sort(arr))
    print(bubble_sort(arr))
    print(merge_sort(arr))