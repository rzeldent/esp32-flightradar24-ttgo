# https://davidmegginson.github.io/ourairports-data/airports.csv
# https://davidmegginson.github.io/ourairports-data/countries.csv

# pip install csv
# pip install collections
# pip install unicodedata
# pip install requests

import csv
import collections
import unicodedata
import requests

download_csv = False

if download_csv:
    # Download the airports.csv file
    request = requests.get(
        'https://davidmegginson.github.io/ourairports-data/airports.csv', allow_redirects=True)
    if request.status_code == 200:
        open('import/airports.csv', 'wb').write(request.content)

    # Download the countries.csv file
    request = requests.get(
        'https://davidmegginson.github.io/ourairports-data/countries.csv', allow_redirects=True)
    if request.status_code == 200:
        open('import/countries.csv', 'wb').write(request.content)

with open('import/countries.csv', encoding='utf-8') as csvfile:
    countries_csv = csv.reader(csvfile, delimiter=',', quotechar='"')
    next(countries_csv, None)  # skip the headers
    countries = []
  
    # "id","code","name","continent","wikipedia_link","keywords"
    for row in countries_csv:
        if not row[1] or len(row[1]) != 2:   # Only with 2 letter country code
            continue
    
        countries.append({'iso_country': row[1], 'name': row[2]})

    sorted_countries= sorted(countries, key=lambda k: k['iso_country'])


with open('import/airports.csv', encoding='utf-8') as csvfile:
    airports_csv = csv.reader(csvfile, delimiter=',', quotechar='"')
    next(airports_csv, None)  # skip the headers
    airports = []
  
    # "id","ident","type","name","latitude_deg","longitude_deg","elevation_ft","continent","iso_country","iso_region","municipality","scheduled_service","gps_code","iata_code","local_code","home_link","wikipedia_link","keywords"
    for row in airports_csv:
        if not row[13] or len(row[13]) != 3:   # Only with 3 letter IATA code
            continue

        airports.append({'iata': row[13], 'name': row[3], 'municipality': row[10], 'iso_country': row[8], 'iso_region': row[9], 'latitude': row[4], 'longitude': row[5], 'elevation': row[6]})

    sorted_airports = sorted(airports, key=lambda k: k['iata'])

    file = open('countries.txt', 'w')
    for country in sorted_countries:
        line = 'const country_t country_' + country['iso_country'] + ' = { "' + country['iso_country'] + '", "' + country['name']+ '", &country_flag_' + country['iso_country'] + ' };\n'
        print(line)
        file.write(unicodedata.normalize('NFKD', line).encode('ascii', errors='ignore').decode('ascii'))

    file.close()

    file = open('airports.txt', 'w')
    for airport in sorted_airports:
        region = airport['iso_region'].split('-')[1]
        line = '{ "' + airport['iata'] + '", "' + airport['name'].replace('"', '\'')+ '", "' + airport['municipality']+ '", "' + region + '", &country_' + airport['iso_country'] + ' ,' +  str(airport['latitude']) + ', ' + str(airport['longitude']) + ', ' + str(airport['elevation'] + ' },\n')
        print(line)
        file.write(unicodedata.normalize('NFKD', line).encode('ascii', errors='ignore').decode('ascii'))

    file.close()
