#!/usr/bin/python3

import re

def custom_strip(string):
    strip_regex = re.compile(r"^\s*(.*\S)\s*$", re.DOTALL)
    mo = strip_regex.search(string)
    if mo != None:
        return mo.group(1)
    else:
        return ""

stripped = custom_strip(" ")
print(repr(stripped))
