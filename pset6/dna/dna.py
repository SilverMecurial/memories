import csv
import sys

if len(sys.argv) != 3:
    print("Usage: python dna.py database.csv sequence.txt")

database = open(sys.argv[1], 'r')  # opens the database file
dbreader = csv.DictReader(database)  # reads the csv
strs = dbreader.fieldnames[1:]  # look at the first row

sequence = open(sys.argv[2], 'r')  # opens the sequence file
s = sequence.read()  # reads the sequence
sequence.close()  # closes the sequence file to save space

counts = {}  # creates dictionary to count STRs
matched = False  # sets bool for later


def longest_chain(str, s):
    i = 0
    while str*(i+1) in s:  # str * 3 = strstrstr
        i += 1  # count the max number of consecutive STR
    return i
        

for str in strs:
    counts[str] = longest_chain(str, s)  # adds i to the array 

    
def match(strs, counts, row):
    for str in strs:
        if counts[str] != int(row[str]):  # if the count of the nth STR is not the same as the current STR then skip
            return False
    return True


for row in dbreader:
    if match(strs, counts, row):
        print(f"{row['name']}")  # once it matches everything it prints the name
        matched = True  # sets matched to true (from earlier) to prevent the next if statement
        database.close()  # saves space
        
if matched == False:
    print("No match")  # if no match, prints no match
    database.close()  # saves space
