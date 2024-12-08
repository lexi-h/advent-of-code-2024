def is_report_safe(report):
    print(f"Checking {report}")
    # initial
    data_is_safe = 1
    diff = report[0] - report[1]
    ascending = True
    if diff > 0:
        ascending = False

    prev_level = report[0]

    #loop
    for level in report[1:]:
        diff = prev_level - level
        if ascending and diff >= 0:
            #bad!
            data_is_safe = 0
        if not ascending and diff <= 0:
            #bad!
            data_is_safe = 0
        if abs(diff) > 3:
            #bad!
            data_is_safe = 0

        prev_level = level

    #ret 1 if data is safe, else 0
    print(data_is_safe)
    return data_is_safe


def main():
    inputfile = open("input", "r")

    safe_reports = 0

    for report in inputfile:
        rawdata = report.split()
        data = []
        for level in rawdata:
            data.append(int(level))
        print(f"FULL REPORT: {data}")

        safe = 0
        for i, val in enumerate(data):
            exclusion = data.pop(i)
            safe = is_report_safe(data)
            if safe:
                safe_reports += safe
                print("YAY")
                break
            data.insert(i, exclusion)

    inputfile.close()

    print(safe_reports)

main()
