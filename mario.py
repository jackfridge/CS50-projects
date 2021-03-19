height = input("Height: ")

while height.isalpha() == True or height == "":
    height = input("Height: ")

height = int(height)

while height < 1 or height > 8:
    height = int(input("Height: "))

for i in range(height):
    # prints out spaces before first hash
    for j in range(height - i - 1):
        print(" ", end="")

    # prints out hashes for the current row
    for j in range(i + 1):
        print("#", end="")

    # no for loop, as the space is constant
    print("  ", end="")

    # prints out the hashes on the right side
    for j in range(i + 1):
        print("#", end="")

    # new line for next row
    print("\n", end="")
