#!/usr/bin/python3

# remove_csv_header.py: removes the header from all CSV files in the current
# working directory

import csv, os

os.makedirs("header_removed", exist_ok=True)

# Loop through every file in the current working directory.
for csv_filename in os.listdir("."):
    if not csv_filename.endswith(".csv"):
        continue # skip non-csv files

    print("Removing header from " + csv_filename + "...")

    # Read the CSV file in (skipping first row).
    csv_rows = []
    csv_file = open(csv_filename)
    csv_reader = csv.reader(csv_file)
    for row in csv_reader:
        if csv_reader.line_num > 1:
            csv_rows.append(row)
    csv_file.close()

    # Write out the CSV file.
    csv_file = open(os.path.join("header_removed", csv_filename), "w",
            newline="")
    csv_writer = csv.writer(csv_file)
    for row in csv_rows:
        csv_writer.writerow(row)
    csv_file.close()
