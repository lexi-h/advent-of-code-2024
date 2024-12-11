import math

#returns dict of rules
# { 31 : [29, 30, 95], 22 : [20, 95]}
def get_rules():
    rulesfile = open("input_rules","r")
    rules = {}
    for line in rulesfile:
        rawinput = line.split("|")
        newrule = [int(rawinput[0]), int(rawinput[1])]
        
        #initialize new key
        if not(newrule[1] in rules):
            rules[newrule[1]] = []

        #add new badnumber to list
        rules[newrule[1]].append(newrule[0])

    rulesfile.close()
    return rules

#returns middle number of list
def get_middle_number(x):
    return x[math.floor(len(x)/2)]

#returns 0 if invalid line
#returns middle number if valid line
def process_line(line, rules):
    # get ints from line
    splitline = line.split(",")
    production = []
    for s in splitline:
        production.append(int(s))


    valid_line = True
    badnumbers = set()
    for item in production:
        if item in badnumbers:
            valid_line = False
            print(f"{item} is bad!!")
            break

        if item in rules:
            for rule in rules[item]:
                badnumbers.add(rule)

    if valid_line:
        return get_middle_number(production)
    else:
        return 0



def main():
    rules = get_rules()
    print(rules)

    grand_total = 0
    productionfile = open("input_production","r")
    for line in productionfile:
        value_of_line = process_line(line, rules)
        grand_total += value_of_line

    productionfile.close()

    print (grand_total)


main()
