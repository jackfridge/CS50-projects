cash = input("Change owed: ")

# make sure the input is not alphanumeric or empty
while cash.isalpha() == True or cash == "":
    cash = input("Change owed: ")

# only accept positive values
while float(cash) <= 0:
    cash = float(input("Change owed: "))

# make cash a float to be calculated in successive while loops
cash = float(cash) * 100.0
counter = 0

# substracts progressively smaller currency until zero is reached
while cash >= 25:
    cash -= 25
    counter += 1
    
while cash >= 10:
    cash -= 10
    counter += 1
    
while cash >= 5:
    cash -= 5
    counter += 1
    
while cash >= 1:
    cash -= 1
    counter += 1
    
print(counter)