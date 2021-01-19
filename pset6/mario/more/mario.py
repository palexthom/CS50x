while True:
    a = 0
    try:
        a = int(input("Height: "))
    except:
        print("Input has to be an integer")
    if a > 0 and a <= 8:
        break

for i in range(a):
    print(" " * (a - i - 1), "#" * (i+1), "  ", "#" * (i+1), sep='')