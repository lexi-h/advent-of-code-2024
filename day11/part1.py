def has_even_digits(p):
    return len(str(p)) % 2 == 0

def left_half(p):
    s = str(p)
    return int(s[:len(s)//2])

def right_half(p):
    s = str(p)
    return int(s[len(s)//2:])

def blink(pebbles):
    newpebbles = []
    for pebble in pebbles:
        if pebble == 0:
            newpebbles.append(1)
        elif has_even_digits(pebble):
            newpebbles.append(left_half(pebble))
            newpebbles.append(right_half(pebble))
        else:
            newpebbles.append(pebble*2024)

    return newpebbles

def main():
    print("concerning the plutonian pebbles...")
    inputfile = open("puzzle_input", "r")

    for line in inputfile:
        a = line
    inputfile.close()

    s = a.split(" ")

    pebbles = []
    for item in s:
        pebbles.append(int(item))



    print(f"starting : {pebbles}")

    for i in range(25):
        pebbles = blink(pebbles)
        print(pebbles)
        print(len(pebbles))


    print(f"final : {pebbles}")
    print(f"len : {len(pebbles)}")

main()
