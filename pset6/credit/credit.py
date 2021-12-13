from cs50 import get_int
# function to get credit card number
import math
# for log later

inp = i = a = b = c = d = e = x = 0
# initialises a whole lot of ints
while int(inp) < 1:
    inp = get_int("Number:")
    
i = inp
x = inp
# for later

if math.log10(inp) <= 12:
    # if input has less than 13 digits, it's invalid
    print("INVALID")
else:
    while i > 0:
        i = int(i / 10)
        # removes last digit from i
        a = int(i % 10)
        # gets last digit of i
        b = int(a * 2)
        i = int(i / 10)
        # removes a to prepare for next digit
        if b >= 10:
            # if b is more than 10, get it as individual digits (eg: 11 as 1 + 1 instead of 11)
            c = int(b % 10)
            d = int(b / 10)
            e += c + d
        else:
            e += b
            # prepares final variable
            
    while inp > 0:
        a = int(inp % 10)
        # gets last digit ie the numbers removed earlier
        inp = int(inp / 100)
        # skips 2 digits to get the next digit
        e += a
        # adds on to final variable
    
if e % 10 == 0:
    # if quotient is 0 ie is divisible by 10
    while x > 100:
        x = int(x / 10)
        # gets first 2 digits of card number
    if 51 <= x <= 55:
        # condition of master is 51 - 55
        print("MASTERCARD")
    elif 40 <= x <= 49:
        # condition of visa is first digit is 4
        print("VISA")
    elif x == 34 or x == 37:
        # condition of amex is 34 or 37
        print("AMEX")
    else:
        print("INVALID")
else:
    # if more than 13 digits but doesn't work with Luhn's formula
    print("INVALID")