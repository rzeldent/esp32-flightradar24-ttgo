# List from: https://www.icao.int/publications/DOC8643/Pages/Search.aspx

# Can be harvested bij chaning the option value for show xxxx entries
# Then copy and save as aircrafts.csv

import csv
import collections
import unicodedata

with open('import/aircrafts.csv', newline='') as csvfile:
    aircrafts_csv = csv.reader(csvfile, delimiter='\t', quotechar='|')
    aircrafts = {}
    # ​​Manufacturer	​Model	​Type Designator	​Description	​Engine Type	​Engine Count	​​WTC
    for row in aircrafts_csv:
        aircrafts[row[2]] = {'manufacturer': row[0], 'type designator': row[1], 'description': row[3], 'engine type': row[4], 'engine count': row[5], 'wtc': row[6], }

    file = open('aircrafts.txt', 'w')
     # Sort the list on Type Designator
    sorted = collections.OrderedDict(sorted(aircrafts.items(), key=lambda v: v[0]));
    for key, aircraft in sorted.items():
        values = ["\"" + key + "\", \"" + aircraft['manufacturer']+"\"", "\"" + aircraft['type designator'] +"\"", "\"" + aircraft['description'] +"\"", "\"" + aircraft['engine type'] +"\"", "\'" + aircraft['engine count'] + "\'"]
        line = "{ " + ", ".join(values) + "}, \n"
        print(line)
        file.write(unicodedata.normalize('NFKD', line).encode('ascii', errors='ignore').decode('ascii'))
    file.close()