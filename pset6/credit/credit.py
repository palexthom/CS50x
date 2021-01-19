from cs50 import get_string


def checksum(numCard: str) -> bool:
    # calculates checksum and returns true/false
    odd = 0
    even = 0

    # loop if even card number
    if len(numCard) % 2 == 0:
        for i in range(0, len(numCard), 2):
            tmp = 2 * int(a[i])
            if tmp > 9:
                odd = odd + 1 + tmp % 10
            else:
                odd += tmp
            even += int(a[i+1])
    # loop if odd card number
    else:
        for i in range(1, len(numCard), 2):
            tmp = 2 * int(a[i])
            if tmp > 9:
                odd = odd + 1 + tmp % 10
            else:
                odd += tmp
        for i in range(0, len(numCard), 2):
            even += int(a[i])

    checksum = odd + even
    #print(f"odd : {odd}, even : {even}, checksum : {checksum}")

    if str(checksum)[-1:] == '0':
        return True
    else:
        return False


while True:
    # get number from user
    a = get_string("Number: ")
    if a != "" and len(a) >= 13:
        break
    else:
        print("INVALID")
        exit(1)

first = a[0]
firstTwo = a[0:2]


if checksum(a):
    if first == "4" and (len(a) == 13 or len(a) == 16):
        print("VISA")
    elif (int(firstTwo) > 50 and int(firstTwo) < 56) and len(a) == 16:
        print("MASTERCARD")
    elif (firstTwo == "34" or firstTwo == "37") and len(a) == 15:
        print("AMEX")