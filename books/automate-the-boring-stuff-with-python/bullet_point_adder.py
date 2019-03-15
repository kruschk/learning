#!/usr/bin/python3

"""
bullet_point_adder.py: adds wikipedia bullet points ('*') to the start of each
line of text on the clipboard
"""

import pyperclip
text = pyperclip.paste()

# todo: separate lines and add asterisks
lines = text.split("\n")
for i in range(len(lines)):
    lines[i] = "* " + lines[i]
text = '\n'.join(lines)

pyperclip.copy(text)
