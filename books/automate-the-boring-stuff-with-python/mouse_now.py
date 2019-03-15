#!/usr/bin/python3

# moust_now.py: displays the mouse cursor's current position.

import pyautogui

print("Press Ctrl+C to quit.")
#TODO: Get and print the mouse coordinates.
try:
    while True:
        x, y = pyautogui.position()
        position_str = "x: " + str(x).rjust(4) + " y: " + str(y).rjust(4)
        print(position_str, end="")
        print("\b"*len(position_str), end="", flush=True)
except KeyboardInterrupt:
    print("\nDone.")
