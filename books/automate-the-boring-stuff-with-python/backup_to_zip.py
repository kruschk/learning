#!/usr/bin/python3

# backup_to_zip.py: Copies an entire folder and its contents into a ZIP file
# whose filename increments.

import os, zipfile

# Backup the entire contents of "folder" into a ZIP file.
def backup_to_zip(folder):
    folder = os.path.abspath(folder) # make sure folder is absolute

    # Figure out the filename this code should use based on what files already
    # exist.
    number = 1
    while True:
        zip_filename = os.path.basename(folder) + "_" + str(number) + ".zip"
        if not os.path.exists(zip_filename):
            break
        number += 1

    # Create the ZIP file.
    print("Creating " + zip_filename + "...")
    backup_zip = zipfile.ZipFile(zip_filename, "w")

    # Walk the entire folder tree and compres the files in each folder.
    for foldername, subfolders, filenames in os.walk(folder):
        print("Adding files in " + foldername + "...")
        # Add the current folder to the ZIP file.
        backup_zip.write(foldername)
        # Add all the files in this folder to the ZIP file.
        for filename in filenames:
            new_base = os.path.basename(folder) + "_"
            if filename.startswith(new_base) and filename.endswith(".zip"):
                continue # don't backup the backup ZIP files
            backup_zip.write(os.path.join(foldername, filename))
    backup_zip.close()
    print("Done.")

backup_to_zip("/home/jonah/Documents/books/Automate the Boring Stuff with Python/")
