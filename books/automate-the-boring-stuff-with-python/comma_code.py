#!/usr/bin/python3

def comma_code(l):
    string = str(l[0])
    for index in range(1, len(l)):
        string += ", "
        if index == len(l) - 1:
            string += "and "
        string += str(l[index])
    return string

spam = ["apple", 5.41, ["hi", "bye"], "bananas", 42, "tofu", "cats"]
print(comma_code(spam))
