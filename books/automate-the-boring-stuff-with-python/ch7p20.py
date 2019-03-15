#!/usr/bin/python3

import re, pyperclip

comma_delim_num = re.compile(r"((?<!\d|,)(\d{1,3},)(\d{3},)*(\d{3})(?!,\d|\d))|((?<!\d|,)(\d{1,3})(?!,\d|\d))")

text = str(pyperclip.paste())
for groups in comma_delim_num.findall(text):
    if groups[0] == "":
        print(groups[4])
    else:
        print(groups[0])
