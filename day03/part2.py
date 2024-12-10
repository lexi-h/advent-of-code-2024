# did some manual formatting on the txt file, lazy solution but 
# small scale enough to be justifiable. 
# know when brute force is an option.
def main():
    f = open("input-final-pt2", "r")
    grand_total = 0
    for line in f:
        tokens = line.split(',')
        result = int(tokens[0]) * int(tokens[1])
        grand_total += result
    f.close()

    print(grand_total)

main()
