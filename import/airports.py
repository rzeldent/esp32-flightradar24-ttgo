# pip install airportsdata
# pip install iso3166

import collections
import airportsdata
from iso3166 import countries
import unicodedata

# Load the list of airports
airports_iata = airportsdata.load('IATA')

file = open('airports.txt', 'w')
# Sort the list on IATA code
sorted = collections.OrderedDict(sorted(airports_iata.items(), key=lambda v: v[0]));
for key, airport in sorted.items():
    country = countries.get(airport['country'])
    values = ["\"" + key + "\", \"" + airport['name']+"\"", "\"" + airport['city']+"\"", "\"" + country.name+"\"",  str(airport['lat']), str(airport['lon']), "&image_" + country.alpha2.lower()]
    line = "{ " + ", ".join(values) + "}, \n"
    print(line)
    file.write(unicodedata.normalize('NFKD', line).encode('ascii', errors='ignore').decode('ascii'))
file.close()
