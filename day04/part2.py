def cross_search(chart):
    running_total = 0
    for row in range(len(chart)):
        for col in range(len(chart[0])):
            if row == 0 or col == 0:
                continue
            if row+1 >= len(chart) or col+1 >= len(chart[0]):
                continue

            targetfound = False
            #fuckit we hardcode
            if chart[row][col] == 'A':
                surroundings = [chart[row-1][col-1], chart[row-1][col+1], chart[row+1][col-1], chart[row+1][col+1]]
                m_count = 0
                s_count = 0
                for letter in surroundings:
                    if letter == 'M':
                        m_count += 1
                    if letter == 'S':
                        s_count += 1

                if m_count == 2 and s_count == 2 and surroundings[0] != surroundings[3]:
                    targetfound = True

            if targetfound:
                running_total += 1

    return running_total

def main():
    inputfile=open("input", "r")
    wordsearch = []
    for line in inputfile:
        wordsearch.append(line)
    inputfile.close()

    #for line in wordsearch:
        #print(line)

    #grand_total = find_words("XMAS", wordsearch) + find_words("SAMX",wordsearch)

    grand_total = cross_search(wordsearch)

    print(f"GRAND TOTAL IS {grand_total}")

main()
