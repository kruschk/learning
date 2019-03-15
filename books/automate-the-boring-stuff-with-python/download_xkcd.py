#!/usr/bin/python3

# download_xkcd.py: downloads every single XKCD comic.

import bs4, os, requests

comic_site = "https://xkcd.com"          # starting url
url = comic_site + "/10/"
os.makedirs("xkcd", exist_ok=True) # store comics in ./xkcd

while not url.endswith("#"):
    # Download the page.
    print("Downloading page " + url + "...")
    resp = requests.get(url)
    resp.raise_for_status()
    soup = bs4.BeautifulSoup(resp.text, features="html.parser")

    # Find the URL of the comic image.
    comic_elem = soup.select("#comic img")
    if comic_elem == []:
        print("Could not find comic image.")
    else:
        try:
            comic_url = "https:" + comic_elem[0].get("src")
            # download the image
            print("Downloading image " + comic_url + "...")
            resp = requests.get(comic_url)
            resp.raise_for_status()
        except requests.exceptions.MissingSchema:
            # skip this comic
            prev_link = soup.select("a[rel='prev']")[0]
            url = comic_site + prev_link.get("href")
            continue
    
        # Save the image to ./xkcd.
        image_file = open(os.path.join("xkcd", os.path.basename(comic_url)), "wb")
        for chunk in resp.iter_content(100000):
            image_file.write(chunk)
        image_file.close()

    # Get the prev button's url.
    prev_link = soup.select("a[rel='prev']")[0]
    url = comic_site + prev_link.get("href")

print("Done.")
