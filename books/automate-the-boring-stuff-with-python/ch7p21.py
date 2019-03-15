#!/usr/bin/python3

import re, pyperclip

comma_delim_num = re.compile(r"[A-Z]\w*\s+Nakamoto")

text = str(pyperclip.paste())
for groups in comma_delim_num.findall(text):
    print(groups)
