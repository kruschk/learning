#!/usr/bin/python3

# stopwatch.py: A simple stopwatch program.

import time

# Display the program's instructions.
print("Press ENTER to begin. Afterward, press ENTER to \"click\" the " +
        "stopwatch. Press Ctrl+C to quit.")
input() # press ENTER to begin
print("Started.")
start_time = time.time() # get the first lap's start time
last_time = start_time
lap_num = 1

# Start tracking the lap times.
try:
    while True:
        input()
        current_time = time.time()
        total_time = round(current_time - start_time, 2)
        lap_time = round(current_time - last_time, 2)
        print("Lap #%s: %s (%s)" %(lap_num, total_time, lap_time), end="")
        lap_num += 1
        last_time = current_time # reset the last lap time
except KeyboardInterrupt:
    # Handle the Ctrl+C exception to keep its error message from displaying.
    print("\nDone.")
