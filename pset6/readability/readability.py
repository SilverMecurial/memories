from cs50 import get_string

L = letters = punctuations = comma = l = s = index = 0
# initialises variables
words = 1
# last word has no space, this accounts for it

text = get_string("Text: ")

L = len(text)

for i in range(L):
    if text[i] == ' ':
        words += 1
        # every word (except the last) has a space after it. Even those with punctuations
    elif text[i] == '.' or text[i] == '!' or text[i] == '?':
        punctuations += 1
        # every sentence can only end with these punctuations
    elif text[i] == ',' or text[i] == '"' or text[i] == "'" or text[i] == ';' or text[i] == ':' or text[i] == '-':
        comma += 1
        # honestly just gets rid of these extra punctuations
    else:
        letters += 1
        # what's left is letters
        
l = letters / words * 100
s = punctuations / words * 100
index = 0.0588 * l - 0.296 * s - 15.8

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    index = round(index)
    # rounds up the index to the right number
    print("Grade", index)