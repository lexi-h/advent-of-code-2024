def main():
    f = open("input-final", "r")
    grand_total = 0
    for line in f:
        tokens = line.split(',')
        result = int(tokens[0]) * int(tokens[1])
        grand_total += result
    f.close()

    print(grand_total)

main()
