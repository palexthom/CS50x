while True:
    answer = 0
    try:
        answer = int(input("Height: "))
    except:
        print("Input has to be an integer")
    if answer > 0 and answer <= 8:
        break

for i in range(answer):
    print(" " * (answer - i - 1), "#" * (i+1), sep='')