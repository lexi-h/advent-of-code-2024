def horizontal_search(target, chart):
    running_total = 0
    for line in chart:
        #print(f"horiz_total: {running_total}")
        #print(line)
        for i, chartletter in enumerate(line):
            j = i
            targetfound = True
            for targetletter in target:
                if targetletter == line[j]:
                    j += 1
                else:
                    targetfound = False
                    break
            if targetfound:
                running_total += 1

    return running_total

def vertical_search(target, chart):
    running_total = 0
    for col in range(len(chart[0])):
        for row in range(len(chart)):
            j = 0
            targetfound = True
            for targetletter in target:
                if row+len(target) > len(chart):
                    targetfound = False
                    break
                if targetletter == chart[row+j][col]:
                    j += 1
                else:
                    targetfound = False
                    break
            if targetfound:
                running_total += 1

        print(f"after col {col}, running total {running_total}")

    return running_total

def diag_l_r_search(target, chart):
    running_total = 0
    for row in range(len(chart)):
        for col in range(len(chart[0])):
            j = 0
            targetfound = True
            for targetletter in target:
                if row+len(target) > len(chart) or col+len(target)-1 > len(chart[0]):
                    targetfound = False
                    break
                if targetletter == chart[row+j][col+j]:
                    j += 1
                else:
                    targetfound = False
                    break
            if targetfound:
                running_total += 1

        print(f"after row {row}, diag_l_r running total {running_total}")

    return running_total

def diag_r_l_search(target, chart):
    running_total = 0
    for row in range(len(chart)):
        for col in range(len(chart[0])):
            j = 0
            targetfound = True
            for targetletter in target:
                if row+len(target) > len(chart) or col-len(target)+1 < 0:
                    targetfound = False
                    break
                if targetletter == chart[row+j][col-j]:
                    j += 1
                else:
                    targetfound = False
                    break
            if targetfound:
                running_total += 1

        print(f"after row {row}, diag_r_l running total {running_total}")

    return running_total





# returns total number of words found
def find_words(target, chart):
    running_total = 0

    running_total += horizontal_search(target, chart)
    running_total += vertical_search(target, chart)
    running_total += diag_l_r_search(target, chart)
    running_total += diag_r_l_search(target, chart)
    '''
    '''

    return running_total


def main():
    inputfile=open("input", "r")
    wordsearch = []
    for line in inputfile:
        wordsearch.append(line)
    inputfile.close()

    #for line in wordsearch:
        #print(line)

    grand_total = find_words("XMAS", wordsearch) + find_words("SAMX",wordsearch)

    print(f"GRAND TOTAL IS {grand_total}")

main()
