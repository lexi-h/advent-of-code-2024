#grep -E -o 'mul[(][[:digit:]]+[,][[:digit:]]+[)]' input-raw > input-clean
grep -E -o '[[:digit:]]+,[[:digit:]]+' input-clean-pt2 > input-final-pt2
