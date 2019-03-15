#!/usr/bin/python3

# table_printer.py: a program to print a multi-dimensional array of data

def table_print(table):
    col_widths = [0]*len(table)
    for i in range(len(table)):
        for j in range((len(table[i]))):
            if len(table[i][j]) > col_widths[i]:
                col_widths[i] = len(table[i][j])
    for j in range((len(table[0]))):
        for i in range(len(table)):
            print(table[i][j].rjust(col_widths[i] + 1), end="")
        print()

table_data = [
        ['apples', 'oranges', 'cherries', 'banana'],
        ['Alice' , 'Bob'    , 'Carol'   , 'David' ],
        ['dogs'  , 'cats'   , 'moose'   , 'goose' ]
]

table_print(table_data)
