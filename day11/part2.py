def sum_pebbles(p):
    running_total = 0
    for k,v in p.items():
        running_total += v

    return running_total

def has_even_digits(p):
    return len(str(p)) % 2 == 0

def left_half(p):
    s = str(p)
    return int(s[:len(s)//2])

def right_half(p):
    s = str(p)
    return int(s[len(s)//2:])

def blink(pebdict):
    newpebs = {}
    for pebble, pebcount in pebdict.items():
        if pebble == 0:
            if 1 in newpebs:
                newpebs[1] += pebcount
            else:
                newpebs[1] = pebcount
        elif has_even_digits(pebble):
            l = left_half(pebble)
            r = right_half(pebble)
            if l in newpebs:
                newpebs[l] += pebcount
            else:
                newpebs[l] = pebcount
            if r in newpebs:
                newpebs[r] += pebcount
            else:
                newpebs[r] = pebcount
        else:
            if pebble*2024 in newpebs:
                newpebs[pebble*2024] += pebcount
            else:
                newpebs[pebble*2024] = pebcount


    return newpebs

def main():
    print("concerning the plutonian pebbles...")
    inputfile = open("puzzle_input", "r")

    for line in inputfile:
        a = line
    inputfile.close()

    s = a.split(" ")

    pebbles = {}
    for item in s:
        if int(item) in pebbles:
            pebbles[int(item)] += 1
        else:
            pebbles[int(item)] = 1



    print(f"starting : {pebbles}")

    for i in range(75):
        pebbles = blink(pebbles)
        print(pebbles)
        print(sum_pebbles(pebbles))
        print(i)


    print(f"final : {pebbles}")
    print(f"size : {sum_pebbles(pebbles)}")

main()
