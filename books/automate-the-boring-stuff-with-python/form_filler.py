#!/usr/bin/python3

# form_filler.py: Automatically fills in a Google form.

import pyautogui, sys, time

# Coordinates of buttons and fields.
name_field = (2575, 408)
submit_button = (2623, 947)
submit_button_colour = (74, 139, 245)
submit_another_link = (2731, 320)

form_data = [
        {'name': 'Alice', 'fear': 'eavesdroppers', 'source': 'wand',
            'robocop': 4, 'comments': 'Tell Bob I said hi.'},
        {'name': 'Bob', 'fear': 'bees', 'source': 'amulet', 'robocop': 4,
            'comments': 'n/a'},
        {'name': 'Carol', 'fear': 'puppets', 'source': 'crystal ball',
            'robocop': 1,
            'comments': 'Please take the puppets out of the break room.'},
        {'name': 'Alex Murphy', 'fear': 'ED-209', 'source': 'money',
            'robocop': 5, 'comments': 'Protect the innocent. Serve the public\
                    trust. Uphold the law.'}
        ]

pyautogui.PAUSE = 0.5

try:
    for person in form_data:
        print(">>> 5 second pause to allow user to press Ctrl+C to quit. <<<")
        time.sleep(5)

        # Wait until the form page has loaded.
        #while not pyautogui.pixelMatchesColor(submit_button[0], submit_button[1],
        #        submit_button_colour):
        #    time.sleep(0.5)

        print("Entering %s info..." %(person["name"]))
        pyautogui.click(name_field[0], name_field[1])

        # Fill out the name field.
        pyautogui.typewrite(person["name"] + "\t")

        # Fill out the greatest fear(s) field.
        pyautogui.typewrite(person["fear"] + "\t")


        # Fill out the Source of Wizard Powers field.
        if person['source'] == 'wand':
            pyautogui.typewrite(['down', '\t'])
        elif person['source'] == 'amulet':
            pyautogui.typewrite(['down', 'down', '\t'])
        elif person['source'] == 'crystal ball':
            pyautogui.typewrite(['down', 'down', 'down', '\t'])
        elif person['source'] == 'money':
            pyautogui.typewrite(['down', 'down', 'down', 'down', '\t'])

        # Fill out the Robocop field.
        if person['robocop'] == 1:
            pyautogui.typewrite([' ', '\t'])
        elif person['robocop'] == 2:
            pyautogui.typewrite(['right', '\t'])
        elif person['robocop'] == 3:
            pyautogui.typewrite(['right', 'right', '\t'])
        elif person['robocop'] == 4:
            pyautogui.typewrite(['right', 'right', 'right', '\t'])
        elif person['robocop'] == 5:
            pyautogui.typewrite(['right', 'right', 'right', 'right', '\t'])

        # Fill out the additional comments field.
        pyautogui.typewrite(person["comments"] + "\t")

        # Click submit.
        pyautogui.press("enter")

        # Wait until form page has loaded.
        print("Clicked submit.")
        time.sleep(5)

        # Click the submit another response link.
        pyautogui.click(submit_another_link[0], submit_another_link[1])
except KeyboardInterrupt:
    print("Exiting early.")
    sys.exit()
