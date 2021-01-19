from cs50 import SQL
import csv
from sys import argv

# Open Db
db = SQL("sqlite:///students.db")

# Read parameters
if len(argv) != 2:
    print("Usage : python import.py <database>")
    exit(1)

# Read csv file in a table
students = []
with open(argv[1], newline='') as csvfile:
    csvread = csv.reader(csvfile)
    for row in csvread:
        students.append([row[0].split(' '), row[1], row[2]])

# Remove first line
del(students[0])

# Add middle name if necessary
for stud in students:
    if len(stud[0]) == 2:
        stud[0] = [stud[0][0], None, stud[0][1]]
    # print(stud)

# Add lines to the database
for stud in students:
    db.execute("INSERT INTO students (first, middle, last, house, birth) \
        VALUES (?, ?, ?, ?, ?)", stud[0][0], stud[0][1], stud[0][2], stud[1], stud[2])