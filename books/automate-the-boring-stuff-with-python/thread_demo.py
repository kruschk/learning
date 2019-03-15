#!/usr/bin/python3

import threading, time
print("Start of program.")

def take_a_nap():
    time.sleep(5)
    print("Wake up!")

thread = threading.Thread(target=take_a_nap)
thread.start()

print("End of program.")
