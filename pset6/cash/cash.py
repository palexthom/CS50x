from cs50 import get_float

while True:
    a = get_float("Change owed: ")
    if a > 0:
        break

# conversion to cents
cents = round(100 * a)

# Calculation of coins
# How many quarters
coins = cents // 25
cents = cents % 25
# Wow many dimes
coins = coins + cents // 10
cents = cents % 10
# How many nickels
coins = coins + cents // 5
cents = cents % 5
# How many pennies
coins = coins + cents

# Printing result
print(coins)
