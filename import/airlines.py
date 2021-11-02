# Inspiration from https://github.com/calda/Airline-Logos

import urllib

for c in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
    for d in "0123456789":
        code = c+d
        url = "https://content.r9cdn.net/rimg/provider-logos/airlines/v/"+code+".png?crop=false&width=300&height=300"
        urllib.request.urlretrieve(url, code+".png")