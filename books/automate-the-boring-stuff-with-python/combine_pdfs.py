#!/usr/bin/python3

# combine_pdfs: combines all the PDFs in the current working directory into a
# single pdf

import os, PyPDF2

# Get all the PDF filenames.
pdf_files = []
for filename in os.listdir("."):
    if filename.endswith(".pdf"):
        pdf_files.append(filename)

pdf_files.sort(key=str.lower)

pdf_writer = PyPDF2.PdfFileWriter()

# Loop through all the PDF files.
for filename in pdf_files:
    pdf_file = open(filename, "rb")
    pdf_reader = PyPDF2.PdfFileReader(pdf_file)

    # Loop through all the pages (except the first) and add them.
    for page_num in range(1, pdf_reader.numPages):
        page = pdf_reader.getPage(page_num)
        pdf_writer.addPage(page)

# Save the resulting PDF to a file.
pdf_output = open("allminutes.pdf", "wb")
pdf_writer.write(pdf_output)
pdf_output.close()
