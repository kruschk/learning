#!/usr/bin/python3

import re, pyperclip

comma_delim_num = re.compile(r"((Alice|Bob|Carol)\s+(eats|pets|throws)\s+(apples|cats|baseballs)\.)", re.IGNORECASE)

text = str(pyperclip.paste())
for groups in comma_delim_num.findall(text):
    print(groups[0])
