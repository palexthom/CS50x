import string

text = input("Text: ")

# Count letters, words and sentences
# L = average number of letters per 100 words in the text
# S = average number of sentences per 100 wors in the text
# index = 0.0588 * L - 0.296 * S - 15.8
# Return round(index).

# Count sentences
sentences = text.count('.') + text.count('!') + text.count('?')

# Count words
words = text.count(' ') + 1

# Count letters
for i in string.punctuation:
    text = text.replace(i, '')
letters = len(text) - text.count(' ')

# Calculate index
L = letters / words * 100
S = sentences / words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

# Return
if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")