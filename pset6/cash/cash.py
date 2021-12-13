from cs50 import get_float

isNegative = True
# creates a bool for loop later

while isNegative:
    n = get_float("Change owed: ")
    if n > 0:
        isNegative = False
        # Breaks the loop when a positive number is given

change = round(n * 100)
# converts change owed to integer

c = 0
# Variable to count number of coins given
while change >= 25:
    change = change - 25
    c += 1
    # counts out 25 cent coins
    
while change >= 10:
    change = change - 10
    c += 1
    # counts out 10 cent coins
    
while change >= 5:
    change = change - 5
    c += 1
    # counts out 5 cent coins
    
while change >= 1:
    change = change - 1
    c += 1
    # counts out 1 cent coins
    
print(c)
# prints out number of coins given back