#!/usr/bin/python3
# autoclicker.py: a simple autoclicker, intended for incremental games

import pyautogui

# pyautogui settings
pyautogui.PAUSE = 0.0
pyautogui.FAILSAFE = True

# set up coordinates to click and the number of iterations
mine_x = 750
mine_y = 700
iterations = 1000
print("Starting the clicker (" + str(iterations) + " iterations)...")

try:
    # slowly move the mouse to the desired point so the user can see
    pyautogui.moveTo(mine_x, mine_y, duration=0.50)
    for i in range(1, iterations + 1):
        # click!
        pyautogui.click(mine_x, mine_y)
        # print progress
        if i%1000 == 0 and i != iterations:
            print(i, end=", ", flush=True)
        elif i == iterations:
            print(i)
except pyautogui.FailSafeException:
    print("\nExiting early after completing " + str(i) + " iteration(s)...")

print("Done.")
