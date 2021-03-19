import cs50

text = cs50.get_string("Text: ")

# since we count spaces for words, init words to 1 instead of 0
characters = 0
words = 1
sentences = 0

# check all characters and add corresponding values for spaces = words, punctuation = sentences...
for char in text:
    if char.isalpha() == True:
        characters += 1
    elif char == " ":
        words += 1
    elif char == "." or char == "?" or char == "!":
        sentences += 1

# average number of letters per 100 words
L = characters * 100.0 / words

# average number of sentences per 100 words
S = sentences * 100.0 / words

# Coleman-Liau index
total = round(0.0588 * L - 0.296 * S - 15.8)

# convert total to the text output (if less than 1 or greater than 16, etc.)
if total < 1.0:
    grade = "Before Grade 1"
elif total >= 16.0:
    grade = "Grade 16+"
else:
    grade = f"Grade {round(total)}"

print(grade)