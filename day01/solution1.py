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

running_total = 0

for itemx, itemy in zip(lista, listb):
    running_total += abs(itemx - itemy)
    
print(running_total)
