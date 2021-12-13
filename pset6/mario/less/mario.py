from cs50 import get_int
# gets function from cs50

outRange = True
# need a bool to use for while loop later
x = n
y = 0
# some variables for later

while outRange:
    n = get_int("Height: ")
    if n >= 1 and n <= 8:
        # range is within 1 and 8
        outRange = False

for i in range(n):
    # C equivalent of for (i = 0; i < n; i++)
    while int(x) > 0:
        # C equivalent of while (x > 0)
        print(' ' * int(x-1), '#' * int(y+1))
        # Use int() to convert str to int for operations
        x = x-1
        y = y+1
        