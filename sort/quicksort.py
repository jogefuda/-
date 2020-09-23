def quick_sort(arr, l, r):
    if (r-l <= 1):
        return
    lr, rl = merge(arr, l, r)
    print(lr, rl)
    quick_sort(arr, l, lr-1)
    quick_sort(arr, rl, r)

def merge(arr, l, r):
    sp = arr[l]
    left = []
    eq = []
    right = []
    for i in range(l+1, r):
        if arr[i] > sp:
            left.append(arr[i])
        elif arr[i] == sp:
            eq.append(sp)
        else:
            right.append(arr[i])
    arr = left+eq+right
    print(arr)
    return len(left), len(left) + len(eq)



        

arr = [1,3,5,6,7]
arr = [3,1,5,7,6]
out = []
quick_sort(arr, 0, len(arr))
print(out)

