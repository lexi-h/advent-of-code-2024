inputfile = open('input', 'r')

lista = []
listb = []

for line in inputfile:
    x, y = line.split()
    lista.append(int(x))
    listb.append(int(y))
    
inputfile.close()

lista.sort()
listb.sort()

processing = True
running_total = 0
it_a = 0
it_b = 0

count_dict = {}

for item in lista:
    count_dict[item] = 0

for item in listb:
    if(item in count_dict):
        count_dict[item] += 1
    
for k,v in count_dict.items():
    running_total += k*v

print(running_total)
