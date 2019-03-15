#!/usr/bin/python3

# Iterative solution
def collatz_iterate(number):
    while number != 1:
        print(number)
        if number%2 == 0:
            number //= 2
        else:
            number = 3*number + 1
    print(number)

# Recursive solution; I think it qualifies as tail recursive.
def collatz_recurse(number):
    print(number)
    if number == 1:
        return 1
    else:
        if number%2 == 0:
            return collatz_recurse(number//2)
        else:
            return collatz_recurse(3*number + 1)

# This is certainly tail recursive
def collatz_tail_recurse(number):
    print(number)
    if number == 1:
        return
    else:
        if number%2 == 0:
            number //= 2
        else:
            number = 3*number + 1
    return collatz_tail_recurse(number);

try:
    number = abs(int(input("Please enter a positive integer: ")))
    print("iterative:")
    collatz_iterate(number)
    print("recursive (may be tail-recursive, not sure):")
    collatz_recurse(number)
    print("tail-recursive:")
    collatz_tail_recurse(number);
except ValueError:
    print("Error: please input a valid integer.")
