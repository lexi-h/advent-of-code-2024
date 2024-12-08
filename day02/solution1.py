inputfile = open("input", "r")

safe_reports = 0

for report in inputfile:
    rawdata = report.split()
    data = []
    for level in rawdata:
        data.append(int(level))
    data_is_safe = 1
    print(data)

    # initial
    diff = data[0] - data[1]
    ascending = True
    if diff > 0:
        ascending = False

    prev_level = data[0]

    #loop
    for level in data[1:]:
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

    #add one if data is safe, add zero if not
    safe_reports += data_is_safe
    print(data_is_safe)



inputfile.close()

print(safe_reports)
