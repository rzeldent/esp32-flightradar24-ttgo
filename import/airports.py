# pip install airportsdata
# pip install iso3166

import airportsdata
from iso3166 import countries
import unicodedata

# Load the list of airports
airports_iata = airportsdata.load('IATA')

file = open('airports.txt', 'w')
for key, airport in airports_iata.items():
    country = countries.get(airport['country']);
    line = "{\"" + key + "\", \"" + airport['name'] + "\", \""+ airport['city'] + "\", \""+ country.name + "\", "+ str(airport['lat'])+ ", "+ str(airport['lon']) + ", &image_" + country.alpha2.lower() + "},\n";
    print(line)
    file.write(unicodedata.normalize('NFKD', line).encode('ascii', errors='ignore').decode('ascii'))

file.close()
 
