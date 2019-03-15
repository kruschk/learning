#!/usr/bin/python3
# lucky.py - opens several Google search results.

import requests, sys, webbrowser, bs4

search_engine = "https://www.google.ca"

print("Googling...") # display text while downloading the Google page
resp = requests.get(search_engine + "/search?q=" + " ".join(sys.argv[1:]))
resp.raise_for_status()

# Retrieve top search result links.
soup = bs4.BeautifulSoup(resp.text, features="html.parser")

# Open a browser tab for each result.
link_elems = soup.select(".r a") # get links (a) inside r classes (.r)
num_open = min(5, len(link_elems))
for i in range(num_open):
    webbrowser.open(search_engine + link_elems[i].get("href"))
