#!/usr/bin/python3
# countdown.py: A simple countdown script.

import time, subprocess

time_left = 5
while time_left > 0:
    print(time_left, end=" ", flush=True)
    time.sleep(1)
    time_left -= 1

# At the end of the countdown, play a sound file.
subprocess.Popen(["see", "alarm.wav"])
