# https://davidmegginson.github.io/ourairports-data/countries.csv

# pip install csv
# pip install collections
# pip install unicodedata
# pip install requests

import csv
import collections
from os import close
import unicodedata
import requests

download_csv = False

if download_csv:
    # Download the countries.csv file
    request = requests.get(
        'https://davidmegginson.github.io/ourairports-data/countries.csv', allow_redirects=True)
    if request.status_code == 200:
        open('import/countries.csv', 'wb').write(request.content)


with open('import/countries.csv', encoding='utf-8') as csvfile:
    countries_csv = csv.reader(csvfile, delimiter=',', quotechar='"')
    next(countries_csv, None)  # skip the headers
    countries = []

    file = open('replace.ps1', 'w')
    file.write('$original_file = airlines.cpp\n')
    file.write('$destination_file =  $original_file + \'.new\'\n')
    file.write('(Get-Content $original_file) | Foreach-Object {\n')
    file.write('$_')
    # "id","code","name","continent","wikipedia_link","keywords"
    for row in countries_csv:
        file.write('  -replace -replace \'"'+ row[2] + '"\',\'&country_' + row[1] +'\' `\n')

    file.write('    } | Set-Content $destination_file\n')
    file.close();



