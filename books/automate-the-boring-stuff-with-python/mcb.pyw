#!/usr/bin/python3
# mcb.pyw: Saves and loads pieces of text to and from the clipboard.
# Usage: mcb.pyw save keyword - saves clipboard contents to keyword.
#        mcb.pyw delete keyword - delete a keyword from the database.
#        mcb.pyw list - loads all keywords to the clipboard.
#        mcb.pyw delete - delete all keywords from the database.
#        mcb.pyw keyword - loads keyword data to the clipboard.

import shelve, pyperclip, sys

# open shelf
mcb_shelf = shelve.open("mcb")

# Save clipboard content.
if len(sys.argv) == 3:
    command = sys.argv[1]
    keyword = sys.argv[2]
    # [save keyword] - save clipboard to database with keyword as its name
    if command.lower() == "save":
        mcb_shelf[keyword] = pyperclip.paste()
    # [delete keyword] - delete keyword from database
    elif command.lower() == "delete" and keyword in mcb_shelf:
        del mcb_shelf[keyword];
elif len(sys.argv) == 2:
    # [list] - list keywords
    if sys.argv[1].lower() == "list":
        pyperclip.copy(str(list(mcb_shelf.keys())))
    # [delete] - delete all keys
    elif sys.argv[1].lower() == "delete":
        for key in mcb_shelf.keys():
            del mcb_shelf[key]
    # [keyword] - load content
    elif sys.argv[1] in mcb_shelf:
        pyperclip.copy(mcb_shelf[sys.argv[1]])
else:
    print("Usage: " + sys.argv[0]
            + " [save keyword|delete keyword|list|delete|keyword]")

# close shelf
mcb_shelf.close()
