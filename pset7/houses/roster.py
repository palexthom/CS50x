from cs50 import SQL
import csv
from sys import argv

# Open Db
db = SQL("sqlite:///students.db")

# Read parameters
if len(argv) != 2:
    print("Usage : python roster.py <house name>")
    exit(1)

query = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

listnames = []

for q in query:  # query is a list of dictionaries
    listnames = []
    listnames.append(q['first'])
    if q['middle'] == None:
        listnames.append(q['last'])
    else:
        listnames.append(q['middle'])
        listnames.append(q['last'])
    print(f"{' '.join(listnames)}, born {q['birth']}")
