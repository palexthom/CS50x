import csv
import os
import re
from sys import argv, exit

# Read parameters
if len(argv) != 3:
    print("missing command-line argument")
    exit(1)

# We will use a dict {(2,8,3), Alice} to store people
# First we make it a list, then we'll convert into a dictionary
people_list = []
people_dict = {}

# Open DNA sequence
f = open(argv[2], "r")
DNA = f.read()

# Open Database
with open(argv[1], newline='') as csvfile:
    csvread = csv.reader(csvfile)
    for row in csvread:
        people_list.append([row[1:], row[0]])

# Extract sequences we will look for
seq = people_list[0][0]
#print(f"Sequences : {' ; '.join(seq)}")

# Remove the first element of the list
people_list.pop(0)

# Make a dictionary out of the list
for i in people_list:
    # Convert strings to integers
    for j in range(len(i[0])):
        i[0][j] = int(i[0][j])
    # Make a dictionary out of the list
    people_dict[tuple(i[0])] = i[1]

# Print dictionary
# for i, j in people_dict.items():
#    print(f"{i} ; {j}")

# Search for DNA sequence
foundtup = []
for j in range(len(seq)):
    imax = len(DNA) // len(seq[j])
    nb_found = 0
    for i in range(51):
        pattern = (f"({seq[j]})" + "{" + f"{i}" + "}")
        found = re.search(pattern, DNA, re.IGNORECASE)
        if found != None and i > nb_found:
            nb_found = i
    foundtup.append(nb_found)

foundtup = tuple(foundtup)

if foundtup in people_dict:
    print(f"{people_dict[foundtup]}")
else:
    print("No match")