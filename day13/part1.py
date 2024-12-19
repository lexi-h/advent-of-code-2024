def test_solution(times_to_press_A, times_to_press_B):
    #print(f"testing A: {times_to_press_A} ==? {int(times_to_press_A)}")
    #print(f"testing B: {times_to_press_B} ==? {int(times_to_press_B)}")

    a_diff = abs(times_to_press_A - round(times_to_press_A))
    b_diff = abs(times_to_press_B - round(times_to_press_B))
    if a_diff > 0.0000001:
        print("A bad!!")
        return 0
    if b_diff > 0.0000001:
        print("B bad!!")
        return 0



    return times_to_press_A * 3 + times_to_press_B

def alt_solve(ax,ay,bx,by,tx,ty):
    print("alt_solve...")
    times_to_press_B = (ty-tx)/(by-bx)
    times_to_press_A = (tx-(bx*times_to_press_B))/ax
    return test_solution(times_to_press_A, times_to_press_B)


def solve(ax,ay,bx,by,tx,ty):
    print(f"{ax} {ay} {bx} {by} {tx} {ty}")

    #avoiding div by zero...
    if ax == ay:
        return alt_solve(ax,ay,bx,by,tx,ty)

    top_term = tx - ((ax * (tx-ty)) / (ax-ay))
    bot_term = bx + ((ax * (by-bx)) / (ax-ay))
    print(f"{top_term} / {bot_term}")
    times_to_press_B = top_term / bot_term

    times_to_press_A = (tx - (bx*times_to_press_B)) / ax

    return test_solution(times_to_press_A, times_to_press_B)


def main():
    inputfile = open("puzzle_input", "r")


    ax = 0
    ay = 0
    bx = 0
    by = 0
    targetx = 0
    targety = 0
    grand_total = 0
    for line in inputfile:
        line = line.strip()
        print(line)
        segments = line.replace('+',' ').replace(',',' ').replace('=',' ').split()
        if line.startswith("Button A:"):
            ax = int(segments[3])
            ay = int(segments[5])
        elif line.startswith("Button B:"):
            bx = int(segments[3])
            by = int(segments[5])
        elif line.startswith("Prize:"):
            targetx = int(segments[2])
            targety = int(segments[4])
            grand_total += solve(ax,ay,bx,by,targetx,targety)


    print(f"grand total tokens {grand_total}")

main()
