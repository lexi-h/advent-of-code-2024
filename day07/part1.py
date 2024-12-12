import copy

def process(result, formula, operator):
    formula = copy.deepcopy(formula)
    # base case
    if len(formula) <= 2:
        is_valid = False
        if operator == "+":
            is_valid = result == formula[0] + formula[1]
        if operator == "*":
            is_valid = result == formula[0] * formula[1]

        print(f"{result} ?= {formula} {operator} : {is_valid}")
        return is_valid

    #recursive case
    else:
        print(f"doing {formula[0]} {operator} {formula[1]}")
        if operator == "+":
            formula[1] = formula[0] + formula[1]
        if operator == "*":
            formula[1] = formula[0] * formula[1]
        formula.pop(0)
        print(f"calling with {formula}...")
        plus_valid = process(result, formula, "+") 
        mult_valid = process(result, formula, "*")
        return plus_valid or mult_valid

    # should never execute
    return None


def main():
    print("concerning the formulas of the bridge that the elephants stole...")
    grand_total = 0
    # process input
    inputfile = open("input","r")
    for line in inputfile:
        given_result, formula = line.split(":")
        formula = formula.split(" ")
        formula = formula[1:]
        for i, x in enumerate(formula):
            formula[i] = int(x)
        given_result = int(given_result)
        print(f"{given_result}: {formula}")
        is_valid = process(given_result, formula, "+") or process(given_result, formula, "*")
        if is_valid:
            grand_total += given_result
            print(f"VALID!!")

        print("")

    print(f"grand total is {grand_total}")

    inputfile.close()

main()
