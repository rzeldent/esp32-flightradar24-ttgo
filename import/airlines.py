# https://flightaware.com/live/fleet/UAL
# pip install csv
# pip install collections
# pip install unicodedata
# pip install requests
# https://en.wikipedia.org/wiki/List_of_airline_codes => csv

import csv
import collections
import unicodedata
import requests
import os.path

logo_path = 'logos/'
get_logo = False

with open('import/airlines.csv', newline='') as csvfile:
    airlines_csv = csv.reader(csvfile, delimiter=',')
    airlines = {}
    
    # IATA	ICAO	Airline	Call sign	Country/Region	Comments
    for row in airlines_csv:
        key = row[1]
        if not key: continue
        if key == 'n/a': continue
        airlines[row[1]] = {'airline': row[2], 'country': row[4] }

    file = open('airlines.txt', 'w')
     # Sort the list on Type Designator
    sorted = collections.OrderedDict(sorted(airlines.items(), key=lambda v: v[0]));
    for key, aircraft in sorted.items():
        logo = 'nullptr'
        logo_file = logo_path + key + '.png'
        if get_logo:
            url = 'https://e0.flightcdn.com/images/airline_logos/90p/'+ key + '.png'
            #url = 'https://flightaware.com/live/fleet/' + key + '.png'
            request = requests.get(url, allow_redirects=True)
            if request.status_code == 200:
                open(logo_file, 'wb').write(request.content)
                logo = '&airline_logo_' + key
        else:
            if os.path.exists(logo_file):
                logo = '&airline_logo_' + key


        values = ["\"" + key + "\", \"" + aircraft['airline']+"\"", "\"" + aircraft['country'] +"\"", logo]
        line = "{ " + ", ".join(values) + "}, \n"
        print(line)
      

        file.write(unicodedata.normalize('NFKD', line).encode('ascii', errors='ignore').decode('ascii'))
    file.close()
