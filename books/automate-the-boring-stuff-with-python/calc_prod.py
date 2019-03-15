#!/usr/bin/python3

import time

# Calculate the product of the first 100,000 positive integers.
def calc_prod():
    product = 1
    for i in range(1, 100001):
        product *= i
    return product

start_time = time.time()
prod = calc_prod()
end_time = time.time()
print("The result is %s digits long." %len(str(prod)))
print("Took %s seconds to calculate." %(end_time - start_time))
end_time2 = time.time()
print("Took %s seconds to complete (holy garbage collection!)." %(end_time2 - start_time))
