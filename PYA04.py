import random
import time

nums = []

def method1():
    n = len(nums)
    max_slice = max((nums[i:j] for i in range(n)
                    for j in range(i+1, n+1)), key=sum)
    return sum(max_slice)

def method2():
    forward_max = 0
    forward_curr = 0
    idx_f_max = 0
    idx_f_curr = 0

    idx_b = len(nums)

    # ugly fix when all values are nagative
    sorted_num = sorted(nums)
    if sorted_num[-1] <= 0:
        return sorted_num[-1]

    total = 0
    for i, n in enumerate(nums):
        if total == 0 and n > 0:
            idx_f_curr = i
            print('start', n)

        total += n
        if total < 0:
            total = 0

        if forward_curr < total:
            forward_curr = total
            print('high: ', forward_curr)
            print('max: ', forward_max)

        if forward_curr > forward_max:
            idx_f_max = idx_f_curr
            forward_max = forward_curr
            forward_curr = 0
    
    total = 0
    for i in range(len(nums)-1, idx_f_max, -1):
        total += nums[i]
        if total < 0:
            idx_b = i
            backward_max = total
            total = 0

    print('index: ', idx_f_max, idx_b)
    total = 0 
    for n in nums[idx_f_max:idx_b]:
        total += n
  
    return total

nums = []
def init():
    global nums
    nums = []
    for i in range(10):
        nums.append(random.randint(-100, 100))

# nums=[9, -7, -8, 3, 9, 3, -2, 9, -9, -8]
# nums=[10, -1, 9, -1, -8, 0, 8, -6, 10, 4]
# nums = [5, -3, -6, -4, -3, -4, -2, 0, -2, -3]
# bug who is wrong ? 
# 2, -6, 8, 2, 3, -8, -8, -10, 6, 10
# -9, 3, 9, -7, -6, -4, 1, -8, 9, 9

def race(func):
    start = time.time()
    ret = func()
    return ret, time.time() - start

# nums = [-46, -47, -44, -66, -61, -31, 42, 2, -77, 70]
# nums = [-53, -39, -35, -95, -76, 3, -26, -48, -21, -1]
# print(nums)
# print(method2())
# exit()
for i in range(1000):
    init()
    ret, t = race(method1)
    ret2, t2 = race(method2)
    if ret != ret2:
        print('----------wrong-----------')
        print(nums)
        print(ret, ret2)
        input()
        
