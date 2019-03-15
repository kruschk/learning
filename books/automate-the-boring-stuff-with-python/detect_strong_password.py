#!/usr/bin/python3

import re, pyperclip

def detect_strong_password(password):
    if len(password) < 8:
        return False
    uppercase_char = re.compile(r".*[A-Z].*", re.DOTALL)
    lowercase_char = re.compile(r".*[a-z].*", re.DOTALL)
    digit = re.compile(r".*\d.*", re.DOTALL)
    if uppercase_char.search(password) and lowercase_char.search(password) and digit.search(password):
        return True
    else:
        return False

text = str(pyperclip.paste())
print(detect_strong_password(text))
