# Inspiration from https://github.com/calda/Airline-Logos
# pip install urllib

import requests

for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
    for d in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789':
        code = c+d
        url = 'https://content.r9cdn.net/rimg/provider-logos/airlines/v/' + code + '.png?crop=false&width=32&height=32'
        request = requests.get(url, allow_redirects=True)
        if request.status_code == 200:
            open('logos/' + code + '.png', 'wb').write(request.content)
