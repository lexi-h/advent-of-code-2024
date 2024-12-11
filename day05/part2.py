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

def fix_bad_production(production, rules):
    production_is_bad = True
    while production_is_bad:
        # fix prod one step

        # find the problem
        valid_line = True
        badnumbers = set()
        problem = -1
        for item in production:
            if item in badnumbers:
                valid_line = False
                print(f"{item} is bad!!")
                problem = item
                break

            if item in rules:
                for rule in rules[item]:
                    badnumbers.add(rule)

        # find the source
        for item in production:
            if item in rules:
                if problem in rules[item]:
                    # found it!
                    source = item
                    print(f"{production}, swapping {source} and {problem}")
                    production[production.index(problem)] = source
                    production[production.index(source)] = problem
                    break
                    

        # check if still bad
        production_is_bad = not line_valid_test(production, rules)

    print(f"fixed! returning {production}")
    return production

def line_valid_test(production, rules):
    valid_line = True
    badnumbers = set()
    for item in production:
        if item in badnumbers:
            valid_line = False
            #print(f"{item} is bad!!")
            break

        if item in rules:
            for rule in rules[item]:
                badnumbers.add(rule)

    return valid_line

def split_the_line(line):
    splitline = line.split(",")
    production = []
    for s in splitline:
        production.append(int(s))

    return production

#returns 0 if invalid line
#returns middle number if valid line
def process_line(line, rules):
    # get ints from line
    production = split_the_line(line)

    if line_valid_test(production, rules):
        return get_middle_number(production)
    else:
        return 0

#returns 0 if invalid line
#returns middle number if valid line
def process_line_pt2(line, rules):
    # get ints from line
    production = split_the_line(line)

    if line_valid_test(production, rules):
        return 0
    else:
        return get_middle_number(fix_bad_production(production,rules))



def main():
    rules = get_rules()
    print(rules)

    grand_total = 0
    productionfile = open("input_production","r")
    for line in productionfile:
        value_of_line = process_line_pt2(line, rules)
        grand_total += value_of_line

    productionfile.close()

    print (grand_total)


main()
